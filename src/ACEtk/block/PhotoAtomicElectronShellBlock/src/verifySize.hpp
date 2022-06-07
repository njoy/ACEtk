static void verifySize( Iterator begin, Iterator end, unsigned int nsh ) {

  // there are at least 3 * NSH - 2 values in the block
  auto size = std::distance( begin, end );
  if ( size < 3 * nsh - 2 ) {

    Log::error( "The size of the XSS subrange in the EPS block should be at "
                "least 3 * NSH - 2" );
    Log::info( "NSH: {}", nsh );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
