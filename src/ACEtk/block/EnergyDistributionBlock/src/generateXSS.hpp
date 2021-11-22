static std::vector< double >
generateXSS( std::vector< DistributionData >&& distributions ) {

  std::size_t size = distributions.size();
  std::vector< double > xss( size );
  std::size_t index = 0;
  for ( auto&& distribution : distributions ) {

    // set the locator
    std::size_t offset = xss.size() - size + 1;
    xss[index] = offset;

    // CAVEAT: for now, the multi-law option is NOT implemented

    // generate the xss array for this distribution
    std::size_t idat = 0;
    std::visit( [ &xss, &idat, offset ] ( const auto& value ) {

                  idat = offset + 3 + 1 + 5;
                  xss.push_back( 0 );                                    // LNW
                  xss.push_back( static_cast< short >( value.LAW() ) );  // LAW
                  xss.push_back( idat );                                 // IDAT
                  xss.push_back( 0 );                                    // NR
                  xss.push_back( 2 );                                    // NE
                  xss.push_back( value.minimumIncidentEnergy() );        // E[0]
                  xss.push_back( value.maximumIncidentEnergy() );        // E[1]
                  xss.push_back( 1. );                                   // P[0]
                  xss.push_back( 1. );                                   // P[1]
                  std::vector< double > temp( value.length() );
                  std::copy( value.begin(), value.end(), temp.begin() );
                  xss.insert( xss.end(), temp.begin(), temp.end() );
                },
                distribution );

        // for those distributions holding internal locators
        if ( std::holds_alternative< OutgoingEnergyDistributionData >( distribution ) ||
             std::holds_alternative< KalbachMannDistributionData >( distribution ) ) {

          // adjust internal locators to start from the beginning of the DLW block
          // instead of what was already there
          auto ne = std::visit( utility::overload{

                                  [] ( const EquiprobableOutgoingEnergyBinData& ) -> std::size_t
                                     { return 0; },
                                  [] ( const DiscretePhotonDistribution& ) -> std::size_t
                                     { return 0; },
                                  [] ( const LevelScatteringDistribution& ) -> std::size_t
                                     { return 0; },
                                  [] ( const GeneralEvaporationSpectrum& ) -> std::size_t
                                     { return 0; },
                                  [] ( const SimpleMaxwellianFissionSpectrum& ) -> std::size_t
                                     { return 0; },
                                  [] ( const EvaporationSpectrum& ) -> std::size_t
                                     { return 0; },
                                  [] ( const EnergyDependentWattSpectrum& ) -> std::size_t
                                     { return 0; },
                                  [] ( const auto& value ) -> std::size_t
                                     { return value.NE(); }
                                },
                                distribution );
          auto nr = std::visit( utility::overload{

                                  [] ( const EquiprobableOutgoingEnergyBinData& ) -> std::size_t
                                     { return 0; },
                                  [] ( const DiscretePhotonDistribution& ) -> std::size_t
                                     { return 0; },
                                  [] ( const LevelScatteringDistribution& ) -> std::size_t
                                     { return 0; },
                                  [] ( const GeneralEvaporationSpectrum& ) -> std::size_t
                                     { return 0; },
                                  [] ( const SimpleMaxwellianFissionSpectrum& ) -> std::size_t
                                     { return 0; },
                                  [] ( const EvaporationSpectrum& ) -> std::size_t
                                     { return 0; },
                                  [] ( const EnergyDependentWattSpectrum& ) -> std::size_t
                                     { return 0; },
                                  [] ( const auto& value ) -> std::size_t
                                     { return value.NB(); }
                                },
                                distribution );
          for ( std::size_t incident = 1; incident < ne + 1; ++incident ) {

            std::size_t locposition = size + idat + 1 + 2 * nr + ne + incident - 1;
            std::size_t relativeloc =
                std::visit( utility::overload{

                              [] ( const EquiprobableOutgoingEnergyBinData& ) -> std::size_t
                                 { return 0; },
                              [] ( const DiscretePhotonDistribution& ) -> std::size_t
                                 { return 0; },
                              [] ( const LevelScatteringDistribution& ) -> std::size_t
                                 { return 0; },
                              [] ( const GeneralEvaporationSpectrum& ) -> std::size_t
                                 { return 0; },
                              [] ( const SimpleMaxwellianFissionSpectrum& ) -> std::size_t
                                 { return 0; },
                              [] ( const EvaporationSpectrum& ) -> std::size_t
                                 { return 0; },
                              [] ( const EnergyDependentWattSpectrum& ) -> std::size_t
                                 { return 0; },
                              [incident] ( const auto& value ) -> std::size_t
                                 { return value.relativeDistributionLocator(incident); }
                            },
                            distribution );
            std::size_t newlocator = idat + relativeloc - 1;
            xss[ locposition ] = newlocator;
          }
        }

    ++index;
  }

  return xss;
}
