Xsdir() = default;
Xsdir( const Xsdir& ) = default;
Xsdir( Xsdir&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] ratios     the atomic weight ratios
 *  @param[in] entries    the file name
 *  @param[in] datapath   the optional datapath
 */
Xsdir( std::map< unsigned int, double > ratios,
       std::vector< XsdirEntry > entries,
       std::optional< std::string > datapath = std::nullopt ) :
  datapath_( std::move( datapath ) ), awr_( std::move( ratios ) ),
  entries_( std::move( entries ) ), indices_( indices( entries_ ) ) {}

/**
 *  @brief Constructor (from a stream)
 *
 *  @param[in] in   the input stream
 */
Xsdir( std::istream& in )
  try : Xsdir( parse( in ) ) {}
  catch( std::exception& e ) {

    Log::info( "Error while constructing an xsdir file" );
    throw e;
  }

Xsdir& operator=( const Xsdir& ) = default;
Xsdir& operator=( Xsdir&& right ) = default;
