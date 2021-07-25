static void verifySize( Iterator begin, Iterator end ) {

  // there are at least 6 values in a table (NB, NE, 2 x and 2 y values)
  auto size = std::distance( begin, end );
  if ( size < 6 ) {

    Log::error( "The size of the XSS subrange in the table should be at least 6" );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
