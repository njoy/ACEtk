static void verifySize( Iterator begin, Iterator dlw, Iterator end,
                        unsigned int nr ) {

  // there are at least ntr values in the LDLW block
  auto size = std::distance( begin, dlw );
  if ( size < nr ) {

    Log::error( "The size of the XSS subrange in the LDLW block should be at "
                "least NR" );
    Log::info( "NR value: {}", nr );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
