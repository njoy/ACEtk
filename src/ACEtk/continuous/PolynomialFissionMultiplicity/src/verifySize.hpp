static void verifySize( Iterator begin, Iterator end,
                        unsigned int numberCoefficients ) {

  auto size = std::distance( begin, end );
  if ( size < numberCoefficients + 2 ) {

    Log::error( "The size of the XSS subrange in the cross section data should "
                "be at least 2 + XSS(2)" );
    Log::info( "XSS(2) value: {}", numberCoefficients );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
