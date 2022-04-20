static std::vector< double >
generateXSS( std::vector< std::vector< double > >&& cosines ) {

  std::vector< double > xss;
  auto ne = cosines.size();
  auto nc = cosines[0].size();
  xss.reserve( ne * nc );

  for ( unsigned int i = 0; i < ne; ++i ) {

    if ( cosines[i].size() != nc ) {

      Log::error( "The number of discrete cosines with incident energy index {} "
                  "is not equal to the expected value", i + 1 );
      Log::info( "Expected size = {}", nc );
      Log::info( "Found size = {}", cosines[i].size() );
      throw std::exception();
    }
    xss.insert( xss.end(), cosines[i].begin(), cosines[i].end() );
  }

  return xss;
}
