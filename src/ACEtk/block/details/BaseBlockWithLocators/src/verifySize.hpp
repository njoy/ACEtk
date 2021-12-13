void verifySize( Iterator begin, Iterator data, Iterator end,
                 unsigned int ntr ) {

  // there are at least ntr values in the locator block
  auto size = std::distance( begin, data );
  if ( size < ntr ) {

    Log::error( "The size of the XSS subrange in the locator part of the {} "
                "block should be at least NTR", this->name() );
    Log::info( "NTR value: {}", ntr );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }

  // there are at least 3 * ntr values in the data block
  size = std::distance( data, end );
  if ( size < 3 * ntr ) {

    Log::error( "The size of the XSS subrange in the data part of the {} block "
                "should be at least 3 * NTR", this->name() );
    Log::info( "NTR value: {}", ntr );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
