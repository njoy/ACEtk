static std::vector< double >
generateXSS( const std::string& name,
             std::vector< long >&& boundaries,
             std::vector< long >&& interpolants,
             std::vector< TabulatedEnergyAngleDistribution >&& distributions,
             std::size_t locb ) {

  // add the distribution data to the xss array
  const auto nr = boundaries.size();
  const auto ne = distributions.size();
  std::vector< double > xss( 1 + 2 * ne );
  xss[0] = ne;
  std::size_t index = 1;
  const auto offset = 1 + 2 * nr + locb;
  for ( const auto& distribution : distributions ) {

    // set the associated value
    xss[index] = distribution.value();

    // set the locator
    xss[index + ne] = static_cast< double >( xss.size() + offset );

    // remake the internal xss array with the proper locators
    const TabulatedEnergyAngleDistribution temp(
              distribution.value(),
              distribution.interpolation(),
              std::move( distribution.distributions() ),
              xss[index + ne] );
    xss.insert( xss.end(), temp.begin(), temp.end() );

    // on to the next distribution
    ++index;
  }

  // insert the interpolation data in the front
  const InterpolationData interpolation( std::string( name ),
                                         std::move( boundaries ),
                                         std::move( interpolants ) );
  xss.insert( xss.begin(), interpolation.begin(), interpolation.end() );

  return xss;
}
