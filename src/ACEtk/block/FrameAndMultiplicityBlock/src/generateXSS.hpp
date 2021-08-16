static std::vector< double >
generateXSS( std::vector< ReferenceFrame >&& frames,
             std::vector< unsigned int >&& multiplicities ) {

  std::vector< double > xss;
  auto ntr = multiplicities.size();
  xss.reserve( ntr );

  if ( frames.size() != ntr ) {

    Log::error( "The size of the TYR subranges are not consistent" );
    Log::info( "NTR value: {}", ntr );
    Log::info( "frames.size(): {}", ntr );
    Log::info( "multiplicities.size(): {}", multiplicities.size() );
    throw std::exception();
  }

  xss.insert( xss.end(), multiplicities.begin(), multiplicities.end() );
  for ( unsigned int i = 0; i < ntr; ++i ) {

    if ( frames[i] == ReferenceFrame::CentreOfMass ) {

      xss[i] *= -1;
    }
  }

  return xss;
}
