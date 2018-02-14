#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing the Neutron (Reaction)" ){
  GIVEN( "An ACE Table for 92235.710nc" ){
    auto ACETable = Table( njoy::utility::slurpFileToMemory("92235.710nc") );

    WHEN( "extracting the Neutron (Reaction)" ){
      int MT{18};
      auto nFission = ContinuousEnergyNeutron::Neutron( ACETable, MT );

      THEN( "the parameters can be verified" ){
        REQUIRE( MT == nFission.ID() );
        REQUIRE( 2 == nFission.Index() );
      }
    } // WHEN

    WHEN( "extracting a non-valid reaction" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( ContinuousEnergyNeutron::Neutron( ACETable, 4004 ) );
      }
    }
  } // GIVEN
} // SCENARIO

