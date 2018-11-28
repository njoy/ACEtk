#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing ContinuousEnergyNeutron::Builder::nu::Builder" ){
  GIVEN( "parent builder" ){
    ContinuousEnergyNeutron::Builder parentBuilder{};
    using FissionNeutronsBuilder = decltype( parentBuilder.reaction( 1 ) );

    struct TestBuilder : ReactionBuilder {
      using ReactionBuilder::construct;
      using ReactionBuilder::ReactionBuilder;
    };

    TestBuilder tb{ 14, parentBuilder };
  } // GIVEN
} // SCENARIO
