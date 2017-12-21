#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO( "Testing the Neutron (Reaction)" ){
  GIVEN( "An ACE Table for 92235.710nc" ){
    auto ACETable = Table( njoy::utility::slurpFileToMemory("92235.710nc") );

    WHEN( "extracting the Neutron (Reaction)" ){
      auto nFission = 
        interpretation::ContinuousEnergyNeutron::Reaction::Neutron( ACETable, 
                                                                    18 );

    } // WHEN
  } // GIVEN
} // SCENARIO

