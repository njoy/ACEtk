/**
 *  @class
 *  @brief The header information in an ACE file
 *
 *  There are multiple version of the header.
 *
 *  The 1.0.0 (or legacy header) contains the following information:
 *    - line 1: ZAID, AW (atomic mass ratio), TZ (temperature in MeV), date
 *    - line 2: description (70 characters), material identifier (10 characters)
 *
 *  The 2.0.0 and 2.0.1 header contains the following information:
 *    - line 1: VERS (header version), SZAID, SRC (evaluation source)
 *    - line 2: AW (atomic mass ratio), TZ (temperature in MeV), date, N (comments)
 *    - line 3 to N+2: comment lines (this is often 2 lines for the 1.0.0
 *      header but that is not guaranteed)
 *
 *  Some ACE files with 2.0.x headers also seem to have some formatting issues
 *  where the data is shifted by a column.
 */
class Header {

  /* fields */
  std::string zaid_;
  double temp_;
  double awr_;
  std::string date_;
  std::vector< std::string > comments_;

  /* auxiliary functions */
  static std::string strip( const std::string& string ) {

    std::string result = string;
    auto notspace = [] ( char c )  { return !std::isspace( c ); };

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
    left( result, length );
    std::rotate( result.begin(),
                 std::next( result.begin(), pivot ),
                 result.end() );
    return result;
  }

public:

  Header( const Header& ) = default;
  Header( Header&& ) = default;

  Header( const std::string& zaid, double awr, double temperature,
          const std::string& date, const std::string& title,
          const std::string& material ) :
    zaid_( strip( zaid ) ), awr_( awr ), temp_( temperature ),
    date_( strip( date ) ),
    comments_( { left( title, 70 ) + right( material, 10 ) } ) {}

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
   *  @brief Return the full ZAID or SZAID of the table
   */
  const std::string& ZAID() const { return this->zaid_; }

  /**
   *  @brief Return the temperature of the table
   */
  double temperature() const { return this->temp_; }

  /* static methods */
  #include "ACEtk/Table/Header/src/print.hpp"

private:

  #include "ACEtk/Table/Header/src/parse.hpp"
};
