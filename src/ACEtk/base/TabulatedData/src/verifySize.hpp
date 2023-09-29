static void verifySize( Iterator begin, Iterator end,
                        unsigned int nr, unsigned int ne ) {

  // there are at least 2 + 2 * nr + 2 * ne values in the tabulated data block
  auto size = std::distance( begin, end );
  if ( size < 2 + 2 * nr + 2 * ne ) {

    Log::error( "The size of the XSS subrange in the tabulated data "
                "block should be at least 2 + 2 * NR + 2 * NE" );
    Log::info( "NR value: {}", nr );
    Log::info( "NE value: {}", ne );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
