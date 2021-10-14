/**
 *  @brief Factory function to make an xsdir from a file
 *
 *  @param[in] filename   the file name
 */
static auto fromFile( const std::string& filename ) {

  std::ifstream in( filename );
  if ( not in ) {

    njoy::Log::error( "Could not open file \'{}\'", filename );
    throw std::exception();
  }
  return Xsdir( in );
}
