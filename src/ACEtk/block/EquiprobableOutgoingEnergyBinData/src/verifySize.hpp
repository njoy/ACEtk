static void verifySize( Iterator begin, Iterator end,
                        unsigned int nr, unsigned int ne, unsigned int net ) {

  auto size = std::distance( begin, end );
  if ( size < 1 + 2 * nr + 1 + ne + 1 + ne * net ) {

    Log::error( "The size of the XSS subrange in the equiprobable outgoing "
                "energy data block should be at least 3 + 2 * NR + NE * ( NET + 1 )" );
    Log::info( "NR value: {}", nr );
    Log::info( "NE value: {}", ne );
    Log::info( "NET value: {}", net );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
