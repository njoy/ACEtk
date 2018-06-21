#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Law4" ){
  std::vector< double > NBT{ 1, 3 };
  std::vector< double > INT{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 3.0, 4.0, 5.0 };
  GIVEN( "valid input values" ){
    WHEN( "constructing a LAW4" ){
      ContinuousEnergyNeutron::ContinuousTabular law4( 
        NBT, INT, energies );

      THEN( "the parameters can be verified" ){
        auto eip = law4.interpolationParameters();
        REQUIRE( ranges::equal( NBT, eip.NBT() ) );
        REQUIRE( ranges::equal( INT, eip.schemes() ) );
        REQUIRE( ranges::equal( energies, law4.incidentEnergies() ) );
      }
    }
  } // GIVEN valid

  GIVEN( "invalid input values" ){
  } // GIVEN invalid
} // SCENARIO
