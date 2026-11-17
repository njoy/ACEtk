/**
 *  @class
 *  @brief The header information in an ACE file
 *
 *  There are multiple version of the header. This is the original header
 *  used by NJOY.
 *
 *  The header contains the following information, fixed column format:
 *    - line 1: ZAID (10 characters), AW (atomic mass ratio, 12 characters),
 *              TZ (temperature in MeV, 12 characters), blank space,
 *              date (10 characters)
 *    - line 2: description (70 characters), material identifier (10 characters)
 */
class Header {

  /* fields */

  std::string vers_;
  std::string zaid_;
  double temp_;
  double awr_;
  std::string date_;
  std::string title_;
  std::string material_;

  /* auxiliary functions */

  static std::string strip( const std::string& string ) {

    std::string result = string;
    auto notspace = [] ( char c ) { return !std::isspace( c ); };

    auto front = std::find_if( result.begin(), result.end(), notspace );
    result.erase( result.begin(), front );
    auto back = std::find_if( result.rbegin(), result.rend(), notspace );
    result.erase( back.base(), result.end() );
    return result;
  }

  static std::string left( const std::string& string, std::size_t length ) {

    std::string result = string;
    result.resize( length, ' ' );
    return result;
  }

  static std::string right( const std::string& string, std::size_t length ) {

    std::string result = string;
    const auto pivot = result.size();
    result = left( result, length );
    std::rotate( result.begin(),
                 std::next( result.begin(), pivot ),
                 result.end() );
    return result;
  }

  template< typename Iterator >
  static Header parse( State< Iterator >& state ) {

    using namespace njoy::tools::disco;

    using Line1 = Record< Character< 10 >,
                          Scientific< 12, 6 >,
                          Scientific< 12, 6 >,
                          Column< 1 >,
                          Character< 10 > >;

    std::string zaid;
    double awr;
    double temp;
    std::string date;

    Line1::read( state.position, state.end, zaid, awr, temp, date );
    ++state.lineNumber;

    if ( awr < 0.0 ) {

      Log::error("Encountered non-physical atomic weight ratio");
      throw std::exception();
    }

    if ( temp < 0.0 ) {

      Log::error("Encountered non-physical temperature");
      throw std::exception();
    }

    using Line2 = Record< Character< 70 >, Character< 10 > >;

    std::string title;
    std::string material;

    Line2::read( state.position, state.end, title, material );
    ++state.lineNumber;

    return  Header( std::move( zaid ), awr, temp, std::move( date ),
                    std::move( title ), std::move( material ) );
  }

public:

  Header() = default;
  Header( const Header& ) = default;
  Header( Header&& ) = default;
  Header& operator=( const Header& ) = default;
  Header& operator=( Header&& ) = default;

  /**
   *  @brief Constructor (legacy header)
   *
   *  @param[in] zaid          the zaid (max 10 characters)
   *  @param[in] awr           the atomic weight ratio (to the neutron mass)
   *  @param[in] temperature   the temperature in MeV
   *  @param[in] date          the date (max 10 characters)
   *  @param[in] title         the title (max 70 characters)
   *  @param[in] material      the material (max 10 characters)
   */
  Header( const std::string& zaid, double awr, double temperature,
          const std::string& date, const std::string& title,
          const std::string& material ) :
    vers_( "1.0.0" ), zaid_( strip( zaid ) ), temp_( temperature ), awr_( awr ),
    date_( strip( date ) ), title_( strip( title ) ),
    material_( strip( material ) ) {}

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator   a buffer iterator
   *
   *  @param[in] state   the buffer state
   */
  template< typename Iterator >
  Header( State< Iterator >& state )
    try : Header( parse( state ) ) {}
    catch( std::exception& e ) {

      Log::info("Error while constructing ACE Table Header");
      throw e;
  }

  /**
   *  @brief Return the header version
   */
  const std::string& VERS() const { return this->vers_; }

  /**
   *  @brief Return the header version
   */
  const std::string& version() const { return this->vers_; }

  /**
   *  @brief Return the full ZAID or SZAID of the table
   */
  const std::string& ZAID() const { return this->zaid_; }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double AWR() const { return this->awr_; }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double atomicWeightRatio() const { return this->AWR(); }

  /**
   *  @brief Return the temperature of the table
   */
  double TEMP() const { return this->temp_; }

  /**
   *  @brief Return the temperature of the table
   */
  double temperature() const { return this->TEMP(); }

  /**
   *  @brief Return the date
   */
  const std::string& date() const { return this->date_; }

  /**
   *  @brief Return the title string
   */
  const std::string& title() const { return this->title_; }

  /**
   *  @brief Return the material string
   */
  const std::string& material() const { return this->material_; }

  template< typename Ostream >
  void print( Ostream& ostream ) const {

    using namespace njoy::tools::disco;

    auto it = std::ostreambuf_iterator< typename Ostream::char_type >( ostream );

    using Line1 = Record< Character< 10 >,
                          FixedPoint< 12, 6>,
                          Scientific< 12, 4 >,
                          Column< 1 >,
                          Character< 10 > >;

    Line1::write( it, right( this->ZAID(), 10 ), this->AWR(), this->TEMP(),
                  right( this->date(), 10 ) );

    using Line2 = Record< Character< 70 >, Character< 10 > >;
    Line2::write( it, left( this->title(), 70 ), right( this->material(), 10 ) );
  }
};
