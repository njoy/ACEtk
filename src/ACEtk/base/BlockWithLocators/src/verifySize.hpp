void verifySize( Iterator begin, Iterator data, Iterator end,
                 unsigned int n ) {

  // there are at least n values in the locator block
  auto size = std::distance( begin, data );
  if ( size < n ) {

    Log::error( "The size of the XSS subrange in the locator part of the {} "
                "block should be at least N", this->name() );
    Log::info( "N value: {}", n );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
