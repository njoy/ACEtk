static std::size_t calculateNumberTransitions( Iterator begin, Iterator end ) {

  const auto size = std::distance( begin, end );

  if ( size%4 != 0 ) {

    Log::error( "The size of the transition data xss arry should be multiples of 4" );
    Log::info( "XSS size: {}", size );
    throw std::exception();
  }

  return size / 4;
}
