/**
 *  @class
 *  @brief The data in an ACE table
 *
 *  The data in an ACE table consists of the following arrays:
 *    - the IZAW array which contains 16 integer, double pairs
 *    - the NXS array which contains information needed to properly interpret
 *      the XSS array
 *    - the JXS array which contains 32 locators to specific blocks in the
 *      XSS array (the meaning of the JXS locators depend on the type of the
 *      ACE table)
 *    - the XSS array which contains the actual data
 */
class Data {

  /* fields */

  std::pair< std::array< int32_t, 16 >,
             std::array< double, 16 > > izaw_;
  std::array< int64_t, 16 > nxs_;
  std::array< int64_t, 32 > jxs_;
  std::vector< double > xss_;

  /* type aliases */

  template< int index >
  using Index = std::integral_constant< int, index >;

  /* auxiliary functions */

  /* helper functions */

  static constexpr const char*
  name( const decltype(xss_)& ){ return "XSS"; }

  static constexpr const char*
  name( const decltype(nxs_)& ){ return "NXS"; }

  static constexpr const char*
  name( const decltype(jxs_)& ){ return "JXS"; }

  static constexpr const char*
  name( const decltype(izaw_.first)& ){ return "IZ"; }

  static constexpr const char*
  name( const decltype(izaw_.second)& ){ return "AW"; }

  template< typename T >
  static void
  verifyIndex( const T& sequence, const std::size_t index ) {

    if ( ( index < 1 ) || ( index > sequence.size() ) ) {

      Log::error( "Illegal index argument" );
      Log::info( "Index value: {}", index );
      Log::info( "{} may be indexed with values between 1 and {} inclusively",
                 name( sequence ), sequence.size() );
      throw std::out_of_range( name( sequence ) );
    }
  }

  template< typename T >
  static decltype(auto)
  fetch( T&& sequence, std::size_t index ) {

    // verify the index only in Debug build mode
    #ifndef NDEBUG
    verifyIndex( sequence, index );
    #endif

    // return the value (index is one-based so subtract 1)
    return sequence[index - 1];
  }

protected:

  #include "ACEtk/Table/Data/Parse.hpp"

private:

  /* constructor */

  /**
   *  @brief Private constructor
   */
  template< typename Iterator >
  Data( State< Iterator >& state,
        decltype(izaw_)&& izaw,
        decltype(nxs_)&& nxs,
        decltype(jxs_)&& jxs ) :
    Data( std::move( izaw ), std::move( nxs ), std::move( jxs ),
          Parse::XSS( state, int64_t{nxs[0]} ) ){}

  /**
   *  @brief Private constructor
   */
  template< typename Iterator >
  Data( State< Iterator >& state,
        decltype(izaw_)&& izaw,
        decltype(nxs_)&& nxs ) :
    Data( state, std::move( izaw ), std::move( nxs ), Parse::JXS( state ) ){}

  /**
   *  @brief Private constructor
   */
  template< typename Iterator >
  Data( State< Iterator >& state,
        decltype(izaw_)&& izaw ) :
    Data( state, std::move( izaw ), Parse::NXS( state ) ){}

public:

  /**
   *  @brief Constructor
   *
   *  @param[in] izaw   the IZAW arrays
   *  @param[in] nxs    the NXS array
   *  @param[in] jxs    the JXS array
   *  @param[in] xss    the XSS array
   */
  Data( decltype(izaw_)&& izaw,
        decltype(nxs_)&& nxs,
        decltype(jxs_)&& jxs,
        decltype(xss_)&& xss ) :
    izaw_( std::move( izaw ) ), nxs_( std::move( nxs ) ),
    jxs_( std::move( jxs ) ), xss_( std::move( xss ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] iz     the IZ array
   *  @param[in] aw     the AW array
   *  @param[in] nxs    the NXS array
   *  @param[in] jxs    the JXS array
   *  @param[in] xss    the XSS array
   */
  Data( decltype(izaw_.first)&& iz,
        decltype(izaw_.second)&& aw,
        decltype(nxs_)&& nxs,
        decltype(jxs_)&& jxs,
        decltype(xss_)&& xss ) :
    izaw_( { std::move( iz ), std::move( aw ) } ), nxs_( std::move( nxs ) ),
    jxs_( std::move( jxs ) ), xss_( std::move( xss ) ) {}

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator   a buffer iterator
   *
   *  @param[in] state   the buffer state
   */
  template< typename Iterator >
  Data( State< Iterator >& state )
    try : Data( state, Parse::IZAW( state ) ) {}
    catch( std::exception& e ) {

      Log::info("Error while constructing ACE Table Data");
      throw e;
    }

  /**
   *  @brief Return the IZ array
   */
  const std::array< int32_t, 16 >& IZ() const { return this->izaw_.first; }

  /**
   *  @brief Return the AW array
   */
  const std::array< double, 16 >& AW() const { return this->izaw_.second; }

  /**
   *  @brief Return the NXS array
   */
  const std::array< int64_t, 16 >& NXS() const { return this->nxs_; }

  /**
   *  @brief Return the JXS array
   */
  const std::array< int64_t, 32 >& JXS() const { return this->jxs_; }

  /**
   *  @brief Return the XSS array
   */
  const std::vector< double >& XSS() const { return this->xss_; }

  /**
   *  @brief Return the IZ array
   */
  std::array< int32_t, 16 >& IZ() { return this->izaw_.first; }

  /**
   *  @brief Return the AW array
   */
  std::array< double, 16 >& AW() { return this->izaw_.second; }

  /**
   *  @brief Return the NXS array
   */
  std::array< int64_t, 16 >& NXS() { return this->nxs_; }

  /**
   *  @brief Return the JXS array
   */
  std::array< int64_t, 32 >& JXS() { return this->jxs_; }

  /**
   *  @brief Return the XSS array
   */
  std::vector< double >& XSS() { return this->xss_; }

  /**
   *  @brief Return a value from the IZ array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int32_t& IZ( std::size_t index ) { return fetch( this->izaw_.first, index ); }

  /**
   *  @brief Return a value from the IZ array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int32_t IZ( std::size_t index ) const { return fetch( this->izaw_.first, index ); }

  /**
   *  @brief Return a value from the AW array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  double& AW( std::size_t index ) { return fetch( this->izaw_.second, index ); }

  /**
   *  @brief Return a value from the AW array
   *
   *  @param[in] index    the index (one-based)
   */
  double AW( std::size_t index ) const { return fetch( this->izaw_.second, index ); }

  /**
   *  @brief Return a value from the NXS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int64_t& NXS( std::size_t index ) { return fetch( this->nxs_, index ); }

  /**
   *  @brief Return a value from the NXS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int64_t NXS( std::size_t index ) const { return fetch( this->nxs_, index ); }

  /**
   *  @brief Return a value from the JXS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int64_t& JXS( std::size_t index ) { return fetch( this->jxs_, index ); }

  /**
   *  @brief Return a value from the JXS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int64_t JXS( std::size_t index ) const { return fetch( this->jxs_, index ); }

  /**
   *  @brief Return a value from the XSS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  double& XSS( std::size_t index ) { return fetch( this->xss_, index ); }

  /**
   *  @brief Return a value from the XSS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  double XSS( std::size_t index ) const { return fetch( this->xss_, index ); }

  /**
   *  @brief Return a value from the XSS array as an integer value
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int IXSS( std::size_t index ) const {

    return static_cast< int >( std::round( fetch( this->xss_, index ) ) );
  }

  /**
   *  @brief Return a subrange of a given length from the XSS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range or if the array goes over its length, an std::out_of_range
   *  exception is thrown.
   *
   *  @param[in] index     the index (one-based)
   *  @param[in] length    the length of the subrange
   */
  auto XSS( std::size_t index, std::size_t length ){

    #ifndef NDEBUG
    verifyIndex( this->xss_, index );
    verifyIndex( this->xss_, index + length - 1 );
    #endif
    const auto left = std::next( this->xss_.begin(), index - 1 );
    const auto right = left + length;
    return njoy::tools::std20::ranges::subrange( left, right );
  }

  /**
   *  @brief Return a subrange of a given length from the XSS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range or if the array goes over its length, an std::out_of_range
   *  exception is thrown.
   *
   *  @param[in] index     the index (one-based)
   *  @param[in] length    the length of the subrange
   */
  auto XSS( std::size_t index, std::size_t length ) const {

    #ifndef NDEBUG
    verifyIndex( this->xss_, index );
    verifyIndex( this->xss_, index + length - 1 );
    #endif
    const auto left = std::next( this->xss_.begin(), index - 1 );
    const auto right = left + length;
    return njoy::tools::std20::ranges::subrange( left, right );
  }

  template< typename Ostream >
  void print( Ostream& ostream ) const {

    using namespace njoy::tools::disco;

    auto it = std::ostreambuf_iterator< typename Ostream::char_type >( ostream );

    using IZAWLine = Record< Integer<7>, FixedPoint<11, 7>,
                             Integer<7>, FixedPoint<11, 7>,
                             Integer<7>, FixedPoint<11, 7>,
                             Integer<7>, FixedPoint<11, 7> >;

    IZAWLine::write( it,
                     this->IZ(1), this->AW(1), this->IZ(2), this->AW(2),
                     this->IZ(3), this->AW(3), this->IZ(4), this->AW(4) );
    IZAWLine::write( it,
                     this->IZ(5), this->AW(5), this->IZ(6), this->AW(6),
                     this->IZ(7), this->AW(7), this->IZ(8), this->AW(8) );
    IZAWLine::write( it,
                     this->IZ(9),  this->AW(9), this->IZ(10), this->AW(10),
                     this->IZ(11), this->AW(11), this->IZ(12), this->AW(12) );
    IZAWLine::write( it,
                     this->IZ(13), this->AW(13), this->IZ(14), this->AW(14),
                     this->IZ(15), this->AW(15), this->IZ(16), this->AW(16) );

    using NXSLine = Record< Integer<9>, Integer<9>,
                            Integer<9>, Integer<9>,
                            Integer<9>, Integer<9>,
                            Integer<9>, Integer<9> >;

    NXSLine::write( it,
                    this->XSS().size(), this->NXS(2), this->NXS(3), this->NXS(4),
                    this->NXS(5), this->NXS(6), this->NXS(7), this->NXS(8) );

    NXSLine::write( it,
                    this->NXS(9), this->NXS(10), this->NXS(11), this->NXS(12),
                    this->NXS(13), this->NXS(14), this->NXS(15), this->NXS(16) );

    using JXSLine = Record< Integer<9>, Integer<9>,
                            Integer<9>, Integer<9>,
                            Integer<9>, Integer<9>,
                            Integer<9>, Integer<9> >;

    JXSLine::write( it,
                    this->JXS(1), this->JXS(2), this->JXS(3), this->JXS(4),
                    this->JXS(5), this->JXS(6), this->JXS(7), this->JXS(8) );

    JXSLine::write( it,
                    this->JXS(9), this->JXS(10), this->JXS(11), this->JXS(12),
                    this->JXS(13), this->JXS(14), this->JXS(15), this->JXS(16) );

    JXSLine::write( it,
                    this->JXS(17), this->JXS(18), this->JXS(19), this->JXS(20),
                    this->JXS(21), this->JXS(22), this->JXS(23), this->JXS(24) );

    JXSLine::write( it,
                    this->JXS(25), this->JXS(26), this->JXS(27), this->JXS(28),
                    this->JXS(29), this->JXS(30), this->JXS(31), this->JXS(32) );

    auto remainingLines = this->XSS().size() / 4;
    auto remainingEntries = this->XSS().size() % 4;
    auto iterator = this->XSS().begin();

    using XSSLine = Record< Scientific< 20, 12 >,
                            Scientific< 20, 12 >,
                            Scientific< 20, 12 >,
                            Scientific< 20, 12 > >;

    while ( remainingLines-- ) {

      XSSLine::write( it, iterator[0], iterator[1], iterator[2], iterator[3] );
      std::advance( iterator, 4 );
    }

    if ( remainingEntries ) {

      while( remainingEntries-- ) {

        Scientific< 20, 12 >::write( *iterator, it );
        ++iterator;
      }
      Record<>::write( it );
    }
  }
};
