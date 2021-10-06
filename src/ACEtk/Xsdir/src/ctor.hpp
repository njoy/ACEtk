Xsdir() = delete;
Xsdir( const Xsdir& ) = default;
Xsdir( Xsdir&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] weights    the atomic weight ratios
 *  @param[in] entries    the file name
 */
Xsdir( std::vector< XsdirEntry > entries,
       std::optional< std::string > datapath = std::nullopt ) :
  datapath_( std::move( datapath ) ), entries_( std::move( entries ) ),
  indices_( indices( entries_ ) ) {}

/**
 *  @brief Constructor (from a stream)
 *
 *  @param[in] in   the input stream
 */
// template< typename Istream >
// Xsdir( Istream& in )
//   try : Xsdir( parse( in ) ) {}
//   catch( std::exception& e ) {
//
//     Log::info( "Error while constructing an xsdir file" );
//     throw e;
// }

Xsdir& operator=( const Xsdir& ) = default;
Xsdir& operator=( Xsdir&& right ) = default;
