static std::vector< double >
generateXSS(
  std::vector< std::vector< ThermalScatteringDiscreteCosines > >&& cosines,
  std::size_t ) {

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
  std::vector< std::vector< ThermalScatteringDiscreteCosinesWithProbability > >&& cosines,
  std::size_t locb ) {

  std::size_t size = cosines.size();
  std::vector< double > xss( size * 2 );
  std::size_t index = 0;
  for ( auto&& data : cosines ) {

    // current value of a locator into the xss array
    // these locators are the actual one-based indices into the xss array
    // so we need to know the size of the xss array prior to this being created
    std::size_t locator = xss.size() + 1;

    // set the locator and number of outgoing energies for the current incident
    // energy
    // Note: historically, these locators are off by 1
    xss[index] = locator + ( locb - 1 ) - 1;
    xss[size + index] = data.size();

    // insert every set of discrete cosines
    for ( auto&& entry : data ) {

      xss.insert( xss.end(), entry.begin(), entry.end() );
    }

    ++index;
  }

  return xss;
}
