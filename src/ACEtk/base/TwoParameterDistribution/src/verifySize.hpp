static void verifySize( Iterator begin, Iterator end ) {

  // there are at least 2 values in the block
  auto size = std::distance( begin, end );
  if ( size < 2 ) {

    Log::error( "The size of the XSS subrange should be at least 2 for a "
                "two parameter distribution" );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
