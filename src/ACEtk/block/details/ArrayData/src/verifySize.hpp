void verifySize( Iterator begin, Iterator end, unsigned int n, unsigned int m ) {

  // there are at least n * m values
  auto size = std::distance( begin, end );
  if ( size < n * m ) {

    Log::error( "The size of the XSS subrange in the {} block should be at "
                "least {} * N", this->name(), m );
    Log::info( "N value: {}", n );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
