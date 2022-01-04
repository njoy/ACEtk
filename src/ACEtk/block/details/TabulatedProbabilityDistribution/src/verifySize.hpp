static void verifySize( Iterator begin, Iterator end,
                        unsigned int numberValues ) {

  auto size = std::distance( begin, end );
  if ( size < 3 * numberValues + 2 ) {

    Log::error( "The size of the XSS subrange in the tabulated "
                "distribution data should be at least 2 + 3 * XSS(2)" );
    Log::info( "XSS(2) value: {}", numberValues );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
