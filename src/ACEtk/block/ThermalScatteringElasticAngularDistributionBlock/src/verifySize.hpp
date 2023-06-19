static void verifySize( std::size_t size, std::size_t ne, std::size_t nc ) {

  if ( size < ne * nc ) {

    Log::error( "The size of the XSS subrange in the elastic thermal scattering "
                "angular distribution block should be at least NE * NC" );
    Log::info( "NE: {}", ne );
    Log::info( "NC: {}", nc );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
