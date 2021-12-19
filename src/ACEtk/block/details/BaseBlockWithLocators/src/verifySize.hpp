void verifySize( Iterator begin, Iterator data, Iterator end,
                 unsigned int nr ) {

  // there are at least nr values in the locator block
  auto size = std::distance( begin, data );
  std::size_t add = this->zero_index_ ? 1 : 0;
  if ( size < nr + add ) {

    if ( this->zero_index_ ) {

      Log::error( "The size of the XSS subrange in the locator part of the {} "
                  "block should be at least NR + 1", this->name() );
    }
    else {

      Log::error( "The size of the XSS subrange in the locator part of the {} "
                  "block should be at least NR", this->name() );
    }
    Log::info( "NR value: {}", nr );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
