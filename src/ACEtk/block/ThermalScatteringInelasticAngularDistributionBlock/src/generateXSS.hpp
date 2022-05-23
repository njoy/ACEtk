static std::vector< double >
generateXSS(
  std::vector< std::vector< ThermalScatteringDiscreteCosines > >&& cosines ) {

  std::vector< double > xss;
  auto ne = cosines.size();
  auto nieb = cosines.front().size();
  for ( unsigned int i = 0; i < ne; ++i ) {

    if ( nieb != cosines[i].size() ) {

      Log::error( "The number of outgoing energies for the incident energy "
                  "with index {} is not equal to the expected number"
                  "expected value", i + 1 );
      Log::info( "Expected number = {}", nieb );
      Log::info( "Found number = {}", cosines[i].size() );
      throw std::exception();
    }

    for ( unsigned int j = 0; j < nieb; ++j ) {

      xss.insert( xss.end(), cosines[i][j].begin(), cosines[i][j].end() );
    }
  }

  return xss;
}

static std::vector< double >
generateXSS(
  std::vector< std::vector< ThermalScatteringDiscreteCosinesWithProbability > >&& cosines ) {

  std::vector< double > xss;
  return xss;
}
