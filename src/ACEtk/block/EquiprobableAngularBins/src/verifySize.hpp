static void verifySize( std::size_t size ) {

  if ( size < 33 ) {

    Log::error( "The size of the XSS subrange in the equiprobable cosine bins "
                "should be at least 33 (for 32 bins)" );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}

static void verifySize( Iterator begin, Iterator end ) {

  auto size = std::distance( begin, end );
  verifySize( size );
}
