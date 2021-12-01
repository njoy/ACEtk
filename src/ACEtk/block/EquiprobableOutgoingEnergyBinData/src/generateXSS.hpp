static std::vector< double >
generateXSS(
  std::vector< long >&& boundaries,
  std::vector< long >&& interpolants,
  std::vector< EquiprobableOutgoingEnergyBins >&& distributions ) {

  // reserve size in the vector
  std::size_t nr = boundaries.size();
  std::size_t ne = distributions.size();
  std::vector< double > xss( 2 + ne ); // NE, list of energies, NET

  // sort distributions
  std::sort( distributions.begin(), distributions.end(),
             [=] ( const auto& left, const auto& right )
                 { return left.incidentEnergy() < right.incidentEnergy(); } );

  // insert the interpolation data
  InterpolationData interpolation( "EquiprobableOutgoingEnergyBinData",
                                   std::move( boundaries ),
                                   std::move( interpolants ) );
  xss.insert( xss.begin(), interpolation.begin(), interpolation.end() );

  // insert the bin data
  xss[ 1 + 2 * nr ] = ne;
  xss[ 2 + 2 * nr + ne ] = distributions.front().numberBins() + 1;
  std::size_t index = 2 + 2 * nr;
  for ( const auto& distribution : distributions ) {

    xss[index] = distribution.incidentEnergy();
    xss.insert( xss.end(), distribution.begin(), distribution.end() );
    ++index;
  }

  return xss;
}
