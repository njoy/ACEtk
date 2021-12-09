static void verifySize( Iterator begin, Iterator xand, Iterator end,
                        unsigned int nr, unsigned int offset ) {

  // there are at least ntr values in the LAND block
  auto size = std::distance( begin, xand );
  if ( size < nr + offset  ) {

    if ( offset == 0 ) {

      Log::error( "The size of the XSS subrange in the LAND block should be at "
                  "least NR + 1" );
    }
    else {

      Log::error( "The size of the XSS subrange in the LAND block should be at "
                  "least NR" );
    }
    Log::info( "NR value: {}", nr );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
