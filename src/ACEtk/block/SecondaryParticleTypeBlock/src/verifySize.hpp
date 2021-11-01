static void verifySize( Iterator begin, Iterator end, unsigned int ntype ) {

  auto size = std::distance( begin, end );
  if ( size < ntype ) {

    Log::error( "The size of the XSS subrange should be at least NTYPE" );
    Log::info( "NTYPE value: {}", ntype );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
