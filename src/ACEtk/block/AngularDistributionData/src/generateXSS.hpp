static std::vector< double >
generateXSS( std::vector< Distribution >&& distributions, std::size_t locb ) {

  const auto ne = distributions.size();
  std::vector< double > xss( 1 + 2 * ne );

  auto incidentEnergy = [] ( const auto& value )
                           { return value.energy(); };

  std::sort( distributions.begin(), distributions.end(),
             [=] ( const auto& left, const auto& right )
                 { return std::visit( incidentEnergy, left )
                          < std::visit( incidentEnergy, right ); } );
  xss[0] = ne;
  std::size_t index = 1;
  for ( const auto& distribution : distributions ) {

    // set the energy value
    xss[index] = std::visit( incidentEnergy, distribution );

    // set the LOCC locator
    if ( std::holds_alternative< IsotropicAngularDistribution >( distribution ) ) {

      // LOCC = 0 for an isotropic distribution
      xss[index + ne] = 0;
    }
    else {

      xss[index + ne] = xss.size() + locb;
      if ( std::holds_alternative< TabulatedAngularDistribution >( distribution ) ) {

        // LOCC is negative for a tabulated distribution
        xss[index + ne] *= -1;
      }
    }

    // insert the xss array
    std::visit( utility::overload{

                  [] ( const IsotropicAngularDistribution& ) {},
                  [&xss] ( const EquiprobableAngularBins& value )
                         { xss.insert( xss.end(),
                                       value.begin(), value.end() ); },
                  [&xss] ( const TabulatedAngularDistribution& value )
                         { xss.insert( xss.end(),
                                       value.begin(), value.end() ); }
                },
                distribution );

    // on to the next distribution
    ++index;
  }

  return xss;
}
