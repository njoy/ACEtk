static std::vector< double >
generateXSS( unsigned int interpolation, int inelastic,
             int absorption, unsigned int type,
             std::vector< ProbabilityTable >&& tables ) {

  std::vector< double > xss( 6 + tables.size() );
  std::size_t bins = tables.front().numberBins();
  xss[0] = tables.size();
  xss[1] = bins;
  xss[2] = interpolation;
  xss[3] = inelastic;
  xss[4] = absorption;
  xss[5] = type;
  unsigned int index = 6;
  for ( const auto& table : tables ) {

    xss[index] = table.incidentEnergy();
    xss.insert( xss.end(), table.begin(), table.end() );
    ++index;
  }
  return xss;
}
