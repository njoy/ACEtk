void verifySize( Iterator begin, 
          Iterator end
        ) {
  
  auto length = std::distance( begin, end );
  unsigned int expectedSize = this->blockLength();
  if ( length != expectedSize ) {
    
    Log::error( "The size of the XSS subrange in the {} block should be {}",
                this->name(), expectedSize );
    Log::info( "XSS.size(): {}", length );
    throw std::exception();
  }
}
