static void verifySize( Iterator begin, Iterator end,
                        unsigned int nra, unsigned int nea,
                        unsigned int nrb, unsigned int neb ) {

  auto size = std::distance( begin, end );
  if ( size < 1 + 2 * nra + 1 + 2 * nea +
              1 + 2 * nrb + 1 + 2 * neb +
              1 ) {

    Log::error( "The size of the XSS subrange in the Watt spectrum data block "
                "should be at least 3 + 2 * ( NRA + NRB ) + 2 * ( NEA + NEB )" );
    Log::info( "NRA value: {}", nra );
    Log::info( "NEA value: {}", nea );
    Log::info( "NRB value: {}", nrb );
    Log::info( "NEB value: {}", neb );
    Log::info( "XSS.size(): {}", size );
    throw std::exception();
  }
}
