static void verifySize( Iterator begin, Iterator sig, Iterator end,
                        unsigned int ntr ) {

  auto size = std::distance( begin, sig );
  if ( size < ntr ) {

    Log::error( "The size of the XSS subrange in the LSIG block should be at least NTR" );
    Log::info( "NTR value: {}", ntr );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
