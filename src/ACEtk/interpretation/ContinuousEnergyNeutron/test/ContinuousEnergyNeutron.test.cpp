#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO( "Testing interpretation:nc" ){
  GIVEN( "An ACE Table for 92235.710nc" ){
    auto ACETable = Table( njoy::utility::slurpFileToMemory("92235.710nc") );
    WHEN( "constructing a ContinuousEnergyNeutron interpretation" ){

      const auto ncTable = interpretation::nc( ACETable );

      THEN( "parameters can be extracted" ){

        REQUIRE( 837481 == ncTable.size() );
        REQUIRE( 92235 == ncTable.ZA() );
      }
    }
  }
}
