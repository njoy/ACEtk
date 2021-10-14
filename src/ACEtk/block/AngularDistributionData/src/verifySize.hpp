static void verifySize( Iterator begin, Iterator end, unsigned int ne ) {

  // there are at least 1 + 2 * ne values in the angular distribution data block
  auto size = std::distance( begin, end );
  if ( size < 1 + 2 * ne ) {

    Log::error( "The size of the XSS subrange in the angular distribution data "
                "block should be at least 1 + 2 * NE" );
    Log::info( "NE value: {}", ne );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
