static void verifySize( Iterator begin, Iterator xand, Iterator end,
                        unsigned int ntr ) {

  // there are at least ntr values in the LAND block
  auto size = std::distance( begin, xand );
  if ( size < ntr ) {

    Log::error( "The size of the XSS subrange in the LAND block should be at "
                "least NTR" );
    Log::info( "NTR value: {}", ntr );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
