static void verifySize( Iterator begin, Iterator end,
                        std::size_t ne, std::size_t nc ) {

  auto size = std::distance( begin, end );
  auto minimum = 1 + ne * nc;
  if ( size < minimum ) {

    Log::error( "The size of the XSS subrange in the column data should be at "
                "equal to 1 + NE * NC" );
    Log::info( "NE: {}", ne );
    Log::info( "NC: {}", nc );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
