static void verifySize( Iterator begin, Iterator end, unsigned int ntr ) {

  auto size = std::distance( begin, end );
  if ( size < ntr ) {

    Log::error( "The size of the XSS subrange should be at least NTR" );
    Log::info( "NTR value: {}", ntr );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
