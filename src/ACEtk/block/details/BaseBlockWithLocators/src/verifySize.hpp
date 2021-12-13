void verifySize( Iterator begin, Iterator data, Iterator end,
                 unsigned int nr ) {

  // there are at least nr values in the locator block
  auto size = std::distance( begin, data );
  if ( size < nr ) {

    Log::error( "The size of the XSS subrange in the locator part of the {} "
                "block should be at least NR", this->name() );
    Log::info( "NR value: {}", nr );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }

  // there are at least 3 * nr values in the data block
  size = std::distance( data, end );
  if ( size < 3 * nr ) {

    Log::error( "The size of the XSS subrange in the data part of the {} block "
                "should be at least 3 * NR", this->name() );
    Log::info( "NTR value: {}", nr );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
