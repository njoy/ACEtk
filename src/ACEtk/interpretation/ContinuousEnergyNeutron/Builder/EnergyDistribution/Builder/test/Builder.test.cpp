#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;
    using ParentBuilder = decltype( CENBuilder.reaction( 14 ) );

    ParentBuilder parentBuilder{ CENBuilder, 14 };
    using EDBuilder = decltype( parentBuilder.energyDistribution() );

    struct TestBuilder : public EDBuilder {
      using EDBuilder::construct;
      using EDBuilder::EDBuilder;
    };

    TestBuilder tb{ parentBuilder };
  GIVEN( "valid inputs" ){
  } // GIVEN
} // SCENARIO
