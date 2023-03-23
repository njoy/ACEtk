static void verifySize( Iterator begin, Iterator sig, Iterator end,
                        unsigned int ntr ) {

  // there are at least ntr values in the LSIG block
  auto size = std::distance( begin, sig );
  if ( size < ntr ) {

    Log::error( "The size of the XSS subrange in the LSIG block should be at "
                "least NTR" );
    Log::info( "NTR value: {}", ntr );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }

  // there are at least 3 * ntr values in the SIG block
  size = std::distance( sig, end );
  if ( size < 3 * ntr ) {

    Log::error( "The size of the XSS subrange in the SIG block should be at "
                "least 3 * NTR" );
    Log::info( "NTR value: {}", ntr );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
