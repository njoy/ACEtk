/**
 *  @brief Constructor
 *
 *  @param[in] izaw   the IZAW array
 *  @param[in] NXS    the NXS array
 *  @param[in] JXS    the JXS array
 *  @param[in] XSS    the XSS array
 */
Data( decltype(izaw_)&& izaw,
      decltype(nxs_)&& nxs,
      decltype(jxs_)&& jxs,
      decltype(xss_)&& xss ) :
  izaw_( std::move( izaw ) ), nxs_( std::move( nxs ) ),
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
