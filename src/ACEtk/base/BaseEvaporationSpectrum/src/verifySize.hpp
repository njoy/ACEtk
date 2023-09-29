static void verifySize( Iterator begin, Iterator end,
                        unsigned int nr, unsigned int ne ) {

  auto size = std::distance( begin, end );
  if ( size < 1 + 2 * nr + 1 + 2 * ne + 1 ) {

    Log::error( "The size of the XSS subrange in the equiprobable outgoing "
                "energy data block should be at least 3 + 2 * NR + 2 * NE" );
    Log::info( "NR value: {}", nr );
    Log::info( "NE value: {}", ne );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
