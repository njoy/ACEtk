void verifySize( Iterator begin, Iterator end, unsigned int ne,
                 unsigned int nieb, unsigned int nc ) {

  // there are at least nr values in the locator block
  auto size = std::distance( begin, end );
  if ( size < ne * nieb * ( 1 + nc ) ) {

    Log::error( "The size of the XSS array in the {} "
                "block should be at least NE * NIEB * ( 1 + NC )", this->name() );
                Log::info( "NE value: {}", ne );
                Log::info( "NIEB value: {}", nieb );
                Log::info( "NC value: {}", nc );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
