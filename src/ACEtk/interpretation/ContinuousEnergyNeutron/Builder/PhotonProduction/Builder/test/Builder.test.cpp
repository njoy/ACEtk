#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing PhotonProduction::Builder" ){
  GIVEN( "parent builder" ){
    struct Builder : public ContinuousEnergyNeutron::Builder{
      public:
        using ContinuousEnergyNeutron::Builder::FissionMultiplicity;
    };
    Builder parentBuilder{};
  } // GIVEN
} // SCENARIO
