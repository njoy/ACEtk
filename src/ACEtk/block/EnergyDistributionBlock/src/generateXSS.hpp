static std::pair< std::vector< double >, std::vector< unsigned int > >
generateXSS( std::vector< EnergyDistributionData >&& distributions,
             std::vector< MultiplicityData >&& multiplicities ) {

  if ( distributions.size() != multiplicities.size() ) {

    Log::error( "The number of distributions and multiplicities should be the same" );
    Log::info( "distributions.size(): {}", distributions.size() );
    Log::info( "multiplicities.size(): {}", multiplicities.size() );
    throw std::exception();
  }

  const auto size = distributions.size();
  std::vector< double > xss( size );
  std::vector< unsigned int > tyr;
  std::size_t index = 0;
  for ( auto&& distribution : distributions ) {

    // current value of a locator into the xss array
    std::size_t locator = xss.size() - size + 1;

    // handle multiplicity
    std::visit(

      utility::overload{

        [ &xss, &tyr, &locator, size ] ( const TabulatedMultiplicity& value ) {

          tyr.insert( tyr.end(), static_cast< double >( 100 + locator ) );
          xss.insert( xss.end(), value.begin(), value.end() );
          locator = xss.size() - size + 1;
        },
        [ &tyr ] ( const unsigned int& value ) {

          tyr.insert( tyr.end(), static_cast< double >( value ) );
        }
      },
      multiplicities[index]
    );

    // set the locator for the current distribution
    xss[index] = locator;

    // multi-law data needs no dummy probabilities
    if ( std::holds_alternative< MultiDistributionData >( distribution ) ) {

      std::visit(

        utility::overload{

          [ &xss, locator ] ( const MultiDistributionData& value ) {

            // remake the internal xss array with the proper locators
            const MultiDistributionData temp(
                      std::move( value.probabilities() ),
                      std::move( value.distributions() ),
                      locator );
            xss.insert( xss.end(), temp.begin(), temp.end() );
          },
          [] ( const auto& ) { /* nothing to do here */ }
        },
        distribution
      );
    }
    else {

      // generate the xss array for this distribution
      std::size_t idat = 0;
      std::visit(

        utility::overload{

          [] ( const MultiDistributionData& ) { /* nothing to do here */ },
          [ &xss, &idat, locator ] ( const auto& value ) {

            idat = locator + 3 + 1 + 5;
            xss.push_back( 0. );                                   // LNW
            xss.push_back( static_cast< double >( value.LAW() ) ); // LAW
            xss.push_back( static_cast< double >( idat ) );        // IDAT
            xss.push_back( 0. );                                   // NR
            xss.push_back( 2. );                                   // NE
            xss.push_back( value.minimumIncidentEnergy() );        // E[0]
            xss.push_back( value.maximumIncidentEnergy() );        // E[1]
            xss.push_back( 1. );                                   // P[0]
            xss.push_back( 1. );                                   // P[1]
          }
        },
        distribution
      );
      std::visit(

        utility::overload{

          [ &xss, idat ] ( const OutgoingEnergyDistributionData& value ) {

            // remake the internal xss array with the proper locators
            decltype(auto) boundaries = value.boundaries();
            decltype(auto) interpolants = value.interpolants();
            const OutgoingEnergyDistributionData temp(
                      { boundaries.begin(), boundaries.end() },
                      { interpolants.begin(), interpolants.end() },
                      std::move( value.distributions() ),
                      idat );
            xss.insert( xss.end(), temp.begin(), temp.end() );
          },
          [ &xss, idat ] ( const KalbachMannDistributionData& value ) {

            // remake the internal xss array with the proper locators
            decltype(auto) boundaries = value.boundaries();
            decltype(auto) interpolants = value.interpolants();
            const KalbachMannDistributionData temp(
                      { boundaries.begin(), boundaries.end() },
                      { interpolants.begin(), interpolants.end() },
                      std::move( value.distributions() ),
                      idat );
            xss.insert( xss.end(), temp.begin(), temp.end() );
          },
          [ &xss, idat ] ( const EnergyAngleDistributionData& value ) {

            // remake the internal xss array with the proper locators
            decltype(auto) boundaries = value.boundaries();
            decltype(auto) interpolants = value.interpolants();
            const EnergyAngleDistributionData temp(
                      { boundaries.begin(), boundaries.end() },
                      { interpolants.begin(), interpolants.end() },
                      std::move( value.distributions() ),
                      idat );
            xss.insert( xss.end(), temp.begin(), temp.end() );
          },
          [ &xss, idat ] ( const AngleEnergyDistributionData& value ) {

            // remake the internal xss array with the proper locators
            decltype(auto) boundaries = value.boundaries();
            decltype(auto) interpolants = value.interpolants();
            const AngleEnergyDistributionData temp(
                      { boundaries.begin(), boundaries.end() },
                      { interpolants.begin(), interpolants.end() },
                      std::move( value.distributions() ),
                      idat );
            xss.insert( xss.end(), temp.begin(), temp.end() );
          },
          [ &xss ] ( const auto& value ) {

            xss.insert( xss.end(), value.begin(), value.end() );
          }
        },
        distribution
      );
    }

    ++index;
  }

  return { std::move( xss ), std::move( tyr ) };
}
