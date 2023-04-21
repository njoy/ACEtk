static void verifySize( Iterator begin, Iterator end,
                        unsigned int numberValues ) {

  auto size = std::distance( begin, end );
  if ( size < 2 * numberValues + 2 ) {

    Log::error( "The size of the XSS subrange in the cross section data should "
                "be at least 2 + 2 * XSS(2)" );
    Log::info( "XSS(2) value: {}", numberValues );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
