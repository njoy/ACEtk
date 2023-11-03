static void verifySize( Iterator begin, Iterator end,
                        unsigned int numberValues ) {

  auto size = std::distance( begin, end );
  if ( size < numberValues + 3 ) {

    Log::error( "The size of the XSS subrange in the production cross section "
                "data should be at least 3 + XSS(3)" );
    Log::info( "XSS(3) value: {}", numberValues );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
