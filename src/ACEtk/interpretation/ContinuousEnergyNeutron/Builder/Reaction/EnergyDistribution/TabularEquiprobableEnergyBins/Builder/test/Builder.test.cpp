#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"
using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( 
  "Testing EnergyDistribution::TabularEquiprobableEnergyBins::Builder" ){
  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  ParentBuilder parentBuilder{};

  auto edBuilder = parentBuilder.reaction( 22 ).energyDistribution();
  using TabBuilder = decltype( edBuilder.tabularEquiprobableEnergyBins() );

  struct TestBuilder : public TabBuilder {
    using TabBuilder::construct;
    using TabBuilder::TabBuilder;
  };

  TestBuilder tb{ angBuilder };
  GIVEN( "valid inputs" ){
  }
  GIVEN( "invalid inputs" ){
  }
} // SCENARIO

