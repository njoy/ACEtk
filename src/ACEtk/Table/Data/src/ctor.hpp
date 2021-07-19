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


private:

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
