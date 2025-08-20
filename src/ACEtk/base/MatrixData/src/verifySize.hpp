void verifySize( Iterator begin, Iterator end, unsigned int nrows, unsigned int ncols ) {
  
  // There must be at least nrows + ncols + nrows * ncols values
  auto size = std::distance( begin, end );
  unsigned int expectedSize = nrows + ncols + nrows * ncols;
  if ( size < expectedSize ) {
    
    Log::error( "The size of the XSS subrange in the {} block should be at least {}",
                this->name(), expectedSize );
    Log::info( "M value: {}, N value: {}", nrows, ncols );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
