static void verifySize( Iterator begin, Iterator end, unsigned int bins ) {

  auto size = std::distance( begin, end );
  if ( size < 6 * bins ) {

    Log::error( "The size of the XSS subrange should be at least 6 * NBINS" );
    Log::info( "NBINS value: {}", bins );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
