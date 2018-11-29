#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( 
    "Testing ContinuousEnergyNeutron::Builder::fissionMultiplicity::Builder" ){
  GIVEN( "parent builder" ){
    struct Builder : protected ContinuousEnergyNeutron::Builder{
      using ContinuousEnergyNeutron::Builder::reactions_;
    };
    Builder parentBuilder{};
    using NubarBuilder = decltype( parentBuilder.fissionMultiplicity() );

    struct TestBuilder : NubarBuilder {
      // using NubarBuilder::construct;
      using NubarBuilder::NubarBuilder;
    };

    TestBuilder tb{ parentBuilder };
  } // GIVEN
} // SCENARIO
