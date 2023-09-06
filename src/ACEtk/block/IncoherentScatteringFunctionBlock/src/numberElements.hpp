static unsigned int numberElements( Iterator begin, Iterator end ) {

  auto size = std::distance( begin, end );
  if ( 21 == size ) {

    return 21;
  }
  else {

    if ( 0 != size%2 ) {

      Log::error( "The size of the XSS subrange in the JINC block for an "
                  "arbitrarily tabulated scattering function should be even" );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
    return size / 2;
  }
}
