static unsigned int numberElements( Iterator begin, Iterator end ) {

  auto size = std::distance( begin, end );
  if ( 110 == size ) {

    return 55;
  }
  else {

    if ( 0 != size % 3 ) {

      Log::error( "The size of the XSS subrange in the JCOH block for"
                  "arbitrarily tabulated form factors should be odd" );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
    return size / 3;
  }
}
