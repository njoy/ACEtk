static void verifySize( std::size_t size, std::size_t ncosines ) {

  if ( size < 1 + ncosines ) {

    Log::error( "The size of the XSS subrange in the discrete cosine data "
                "should be at least 1 + the number of discrete cosines" );
    Log::info( "Number discrete cosines: {}", ncosines );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}

static void verifySize( Iterator begin, Iterator end, std::size_t ncosines ) {

  auto size = std::distance( begin, end );
  verifySize( size, ncosines );
}
