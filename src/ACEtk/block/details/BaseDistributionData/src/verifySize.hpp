static void verifySize( Iterator begin, Iterator end,
                        unsigned int nr, unsigned int ne, unsigned int nc ) {

  // there are at least 2 + 2 * nr + nc * ne values in the distribution data block
  auto size = std::distance( begin, end );
  if ( size < 2 + 2 * nr + nc * ne ) {

    Log::error( "The size of the XSS subrange in the distribution data "
                "block should be at least 2 + 2 * NR + NC * NE" );
    Log::info( "NR value: {}", nr );
    Log::info( "NE value: {}", ne );
    Log::info( "NC value: {}", ne );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
