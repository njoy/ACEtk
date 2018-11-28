#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing ContinuousEnergyNeutron::Builder::nu::Builder" ){
  GIVEN( "parent builder" ){
    ContinuousEnergyNeutron::Builder parentBuilder{};
    using FissionNeutronsBuilder = decltype( parentBuilder.fissionNeutrons() );

    struct TestBuilder : FissionNeutronsBuilder {
      using FissionNeutronsBuilder::construct;
      using FissionNeutronsBuilder::FissionNeutronsBuilder;
    };

    TestBuilder tb{ parentBuilder };
  } // GIVEN
} // SCENARIO
