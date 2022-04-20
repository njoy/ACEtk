static void verifySize( std::size_t size, std::size_t nbins ) {

  if ( size < 1 + nbins + 1 ) {

    Log::error( "The size of the XSS subrange in the equiprobable cosine bins "
                "should be at least 2 + the number of bins" );
    Log::info( "Number bins: {}", nbins );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}

static void verifySize( Iterator begin, Iterator end, std::size_t nbins ) {

  auto size = std::distance( begin, end );
  verifySize( size, nbins );
}
