static void verifySize( Iterator begin, Iterator end, unsigned int ne ) {

  // there are at least 1 + nc * ne values in the distribution data block
  auto size = std::distance( begin, end );
  if ( size < 2 + 2 * ne ) {

    Log::error( "The size of the XSS subrange in the distribution data "
                "block should be at least 2 + 2 * NE" );
    Log::info( "NE value: {}", ne );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
