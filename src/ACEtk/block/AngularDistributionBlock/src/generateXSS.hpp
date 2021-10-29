static std::vector< double >
generateXSS( std::vector< DistributionData >&& distributions ) {

  std::size_t size = distributions.size();
  std::vector< double > xss( size );
  std::size_t index = 0;
  for ( const auto& distribution : distributions ) {

    // set the locator
    std::size_t offset = xss.size() - size + 1;
    xss[index] = offset;

    // reset locator and/or insert xss array
    if ( std::holds_alternative< FullyIsotropicDistribution >( distribution ) ) {

      xss[index] = 0;
    }
    else {

      if ( std::holds_alternative< DistributionGivenElsewhere >( distribution ) ) {

        xss[index] = -1;
      }
      else {

        decltype(auto) value = std::get< AngularDistributionData >( distribution );
        xss.insert( xss.end(), value.begin(), value.end() );

        // adjust internal locators to start from the beginning of the AND block
        // instead of what was already there
        auto ne = value.numberIncidentEnergies();
        for ( std::size_t incident = 1; incident < ne + 1; ++incident ) {

          std::size_t locposition = size + offset + ne + incident - 1;
          int oldlocator = xss[ locposition ];
          int newlocator = oldlocator == 0
              ? 0
              : offset + value.relativeAngularDistributionLocator(incident) - 1;
          if ( oldlocator < 0 ) {

            newlocator *= -1;
          }
          xss[ locposition ] = newlocator;
        }
      }
    }

    ++index;
  }

  return xss;
}
