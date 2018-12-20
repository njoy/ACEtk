#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing Reaction::EnergyDistribution::Builder" ){
    ContinuousEnergyNeutron::Builder topBuilder{};
    using ReacBuilder = decltype( topBuilder.reaction( 102 ) );

    ReacBuilder reacBuilder{ topBuilder, 102 };

    using EDBuilder = decltype( reacBuilder.energyDistribution( ) );

    struct TestBuilder : public EDBuilder{
      using EDBuilder::construct;
      using EDBuilder::EDBuilder;
    };

  std::vector< double > boundaries{ 0.0, 3.0 };
  std::vector< double > schemes{ 2.0, 1.0 };
  std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
  std::vector< double > values{ 2.1, 2.2, 2.5, 2.5 };

  TestBuilder tb{ reacBuilder };
  GIVEN( "valid inputs" ){
    tb.boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) )
      .probabilities( njoy::utility::copy( values ) );

    THEN( "the values can be verified" ){
      auto energyDistribution = tb.construct();
    }
  } // GIVEN
} // SCENARIO
