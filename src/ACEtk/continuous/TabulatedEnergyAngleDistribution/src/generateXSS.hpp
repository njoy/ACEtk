static std::vector< double >
generateXSS( const std::string&,
             unsigned int interpolation,
             std::vector< TabulatedAngularDistributionWithProbability >&& distributions,
             std::size_t locb ) {

  // add the distribution data to the xss array
  const auto ne = distributions.size();
  std::vector< double > xss( 1 + 4 * ne );
  xss[0] = static_cast< double >( ne );
  std::size_t index = 1;
  const auto offset = 1 + locb;
  for ( const auto& distribution : distributions ) {

    // set the associated energy, probability and cumulative probability value
    xss[index] = distribution.energy();
    xss[index + ne] = distribution.probability();
    xss[index + 2 * ne] = distribution.cumulativeProbability();

    // set the locator
    xss[index + 3 * ne] = static_cast< double >( xss.size() + offset );

    // insert the xss array
    xss.insert( xss.end(), distribution.begin(), distribution.end() );

    // on to the next distribution
    ++index;
  }

  // insert the interpolation data in the front
  xss.insert( xss.begin(), static_cast< double >( interpolation ) );

  return xss;
}
