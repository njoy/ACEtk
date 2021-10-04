XsdirEntry() = default;
XsdirEntry( const XsdirEntry& ) = default;
XsdirEntry( XsdirEntry&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] zaid            the zaid
 *  @param[in] awr             the atomic weight ratio (to the neutron mass)
 *  @param[in] filename        the file name
 *  @param[in] address         the starting address or line
 *  @param[in] length          the length of the file
 *  @param[in] access          the access path for the file (optional)
 *  @param[in] recordlength    the length of a record (optional)
 *  @param[in] entries         the number of entries per record (optional)
 *  @param[in] temperature     the temperature of the file (optional)
 *  @param[in] ptable          flag to indicate if a probability table is present
 */
XsdirEntry( std::string zaid, double awr, std::string filename,
            unsigned int filetype, unsigned int address, unsigned int length,
            std::optional< std::string > access = std::nullopt,
            std::optional< unsigned int > recordlength = std::nullopt,
            std::optional< unsigned int > entries = std::nullopt,
            std::optional< double > temperature = std::nullopt,
            bool ptable = false ) :
  zaid_( std::move( zaid ) ),  awr_( awr ), filename_( std::move( filename ) ),
  access_( std::move( access ) ), filetype_( filetype ), address_( address ),
  tablelength_( length ), recordlength_( std::move( recordlength ) ),
  entries_( std::move( entries ) ), temperature_( std::move( temperature ) ),
  ptable_( ptable ) {}

/**
 *  @brief Constructor (ASCII file)
 *
 *  @param[in] zaid            the zaid
 *  @param[in] awr             the atomic weight ratio (to the neutron mass)
 *  @param[in] filename        the file name
 *  @param[in] address         the starting address or line
 *  @param[in] length          the length of the file
 *  @param[in] temperature     the temperature of the file (optional)
 *  @param[in] ptable          flag to indicate if a probability table is present
 *  @param[in] access          the access path for the file (optional)
 */
XsdirEntry( std::string zaid, double awr, std::string filename,
            unsigned int address, unsigned int length,
            std::optional< double > temperature = std::nullopt,
            bool ptable = false,
            std::optional< std::string > access = std::nullopt ) :
  XsdirEntry( std::move( zaid ), awr, std::move( filename ),
              1, address, length, std::move( access ),
              std::nullopt, std::nullopt, std::move( temperature ), ptable ) {}

/**
 *  @brief Constructor (from a stream)
 *
 *  @param[in] in   the input stream
 */
template< typename Istream >
XsdirEntry( Istream& in )
  try : XsdirEntry( parse( in ) ) {}
  catch( std::exception& e ) {

    Log::info( "Error while constructing an xsdir entry" );
    throw e;
}

XsdirEntry& operator=( const XsdirEntry& ) = default;
XsdirEntry& operator=( XsdirEntry&& right ) = default;
