Header201() = default;
Header201( const Header201& ) = default;
Header201( Header201&& ) = default;
Header201& operator=( const Header201& ) = default;
Header201& operator=( Header201&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] szaid         the szaid (max 10 characters)
 *  @param[in] source        the source of the file
 *  @param[in] awr           the atomic weight ratio (to the neutron mass)
 *  @param[in] temperature   the temperature in MeV
 *  @param[in] date          the date (max 10 characters)
 *  @param[in] comments      the material (max 10 characters)
 */
Header201( const std::string& szaid, const std::string& source,
           double awr, double temperature, const std::string& date,
           const std::vector< std::string >& comments ) :
  szaid_( strip( szaid ) ), src_( strip( source ) ),
  awr_( awr ), temp_( temperature ), date_( strip( date ) ),
  comments_( std::move( comments ) ) {}

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator   a buffer iterator
 *
 *  @param[in] state   the buffer state
 */
template< typename Iterator >
Header201( State< Iterator >& state )
  try : Header201( parse( state ) ) {}
  catch( std::exception& e ) {

    Log::info("Error while constructing ACE Table Header201");
    throw e;
}
