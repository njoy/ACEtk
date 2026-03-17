static void verifySize( Iterator begin, Iterator end, unsigned int nsec ) {

  auto size = std::distance( begin, end );
  if ( size != 1 + nsec ) {

    Log::error( "The size of the XSS subrange should be NSEC + 1" );
    Log::info( "NSEC value: {}", nsec );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
