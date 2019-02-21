#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::GeneralEvaporationSpectrum::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
    using GESBuilder = decltype( parentBuilder.generalEvaporationSpectrum() );

    struct TestBuilder : public GESBuilder {
      using GESBuilder::construct;
      using GESBuilder::GESBuilder;
    };

  TestBuilder gES( parentBuilder );

  GIVEN( "valid inputs" ){
    std::vector< int > boundaries{ 0, 3 };
    std::vector< int > schemes{ 2, 1 };
    std::vector< double > energies{ 1.0, 2.0 };
    std::vector< double > theta{ 2.5, 3.7 };

    gES.boundaries( njoy::utility::copy( boundaries ) )
       .schemes( njoy::utility::copy( schemes ) )
       .energies( njoy::utility::copy( energies ) )
       .effectiveTemperature( njoy::utility::copy( theta ) );

    std::vector< double > X{ 1.0, 2.2, 5.4 };

    WHEN( "not everything has been built" ){
      CHECK_THROWS_AS(
          gES.construct(),
          std::bad_optional_access&
      );
    }

    gES.equiprobableBins( njoy::utility::copy( X ) );

    auto distribution = gES.construct();
    THEN( "the values can be verified" ){
      auto tab = distribution.tabulatedEffectiveTemperature;
      auto parameters = tab.parameters;
      CHECK( ranges::equal( boundaries, parameters->first ) );
      CHECK( ranges::equal( schemes, parameters->second ) );
      CHECK( ranges::equal( energies, tab.x ) );
      CHECK( ranges::equal( theta, tab.y ) );
      CHECK( ranges::equal( X, distribution.spectrum ) );

    }
  }
} // SCENARIO
