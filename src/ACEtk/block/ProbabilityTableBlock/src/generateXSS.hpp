static std::vector< double >
generateXSS( unsigned int interpolation, int inelastic,
             int absorption, unsigned int type,
             std::vector< ProbabilityTable >&& tables ) {

  std::vector< double > xss( 6 + tables.size() );
  const auto bins = tables.front().numberBins();
  xss[0] = static_cast< double >( tables.size() );
  xss[1] = static_cast< double >( bins );
  xss[2] = static_cast< double >( interpolation );
  xss[3] = static_cast< double >( inelastic );
  xss[4] = static_cast< double >( absorption );
  xss[5] = static_cast< double >( type );
  unsigned int index = 6;
  for ( const auto& table : tables ) {

    xss[index] = table.incidentEnergy();
    xss.insert( xss.end(), table.begin(), table.end() );
    ++index;
  }
  return xss;
}
