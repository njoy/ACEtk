static void verifySize( Iterator begin, Iterator end ) {

  // there are at least 6 values in a table (NB, NE, 2 x and 2 y values)
  auto size = std::distance( begin, end );
  if ( size < 6 ) {

    Log::error( "The size of the XSS subrange in the table should be at least 6" );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }

  // verify size with respect to NB
  std::size_t nb = *begin;
  if ( nb > 0 ) {

    if ( size < 2 + 2 * nb ) {

      Log::error( "The size of the XSS subrange in the table should be at least "
                  "2 + 2 * nb" );
      Log::info( "NB: {}", nb );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  // verify size with respect to NE
  std::size_t ne = *std::next( begin, 1 + 2 * nb );
  if ( ne == 0 ) {

    Log::error( "The number of energy values should be larger than zero" );
    throw std::exception();
  }
  else {

    if ( size < 2 + 2 * nb + 2 * ne ) {

      Log::error( "The size of the XSS subrange in the table should be at least "
                  "2 + 2 * nb + 2 * ne" );
      Log::info( "NB: {}", nb );
      Log::info( "NE: {}", nb );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }
}
