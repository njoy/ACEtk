#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation::ContinuousEnergyNeutron;

SCENARIO( "Testing the PhotonProduction (Reaction)" ){
  GIVEN( "An ACE Table for 92235.710nc" ){
    auto ACETable = Table( njoy::utility::slurpFileToMemory("92235.710nc") );

    WHEN( "extracting the Neutron (Reaction)" ){
      auto pProduction = Reaction::PhotonProduction( ACETable, 4004 );

      THEN( "the parameters can be verified" ){
        REQUIRE( 4004 == pProduction.ID() );
        REQUIRE( 3 == pProduction.Index() );
      }
    } // WHEN

    WHEN( "extracting a non-valid reaction" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( Reaction::PhotonProduction( ACETable, 18 ) );
      }
    }
  } // GIVEN
} // SCENARIO
