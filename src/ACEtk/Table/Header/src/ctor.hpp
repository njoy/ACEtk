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
  vers_( "1.0.0" ), zaid_( strip( zaid ) ),  awr_( awr ), temp_( temperature ),
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
