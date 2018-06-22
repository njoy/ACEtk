#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Law1" ){
  std::vector< double > NBT{ 1, 5 };
  std::vector< double > INT{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector< double > outgoingTables{
    1.0, 2.0, 3.0, 4.0,
    1.1, 2.1, 3.1, 4.1,
    1.2, 2.2, 3.2, 4.2,
    1.3, 2.3, 3.3, 4.3,
    1.4, 2.4, 3.4, 4.4,
  };
  ENDFInterpolationParameters EIP( NBT, INT );
  GIVEN( "valid input values" ){
    WHEN( "constructing a LAW1" ){
      ContinuousEnergyNeutron::TabularEquiprobableEnergyBins law1( 
          NBT, INT, energies, 4, outgoingTables );

      THEN( "the parameters can be verified" ){

        auto eip = law1.interpolationParameters();
        REQUIRE( ranges::equal( NBT, eip.NBT() ) );
        REQUIRE( ranges::equal( INT, eip.schemes() ) );
        REQUIRE( ranges::equal( energies, law1.incidentEnergies() ) );

        auto oET = law1.outgoingEnergyTables();
        REQUIRE( 5 == oET.size() );
        REQUIRE( ranges::equal( outgoingTables, oET | ranges::view::join ) );
      }
    }
  }
  GIVEN( "invalid inputs" ){
    WHEN( "outgoingTables is wrong size" ){
      std::vector< double > outgoingTables{
        1.0, 2.0, 3.0, 4.0,
        1.1, 2.1, 3.1, 4.1,
        1.2, 2.2, 3.2, 4.2,
        1.3, 2.3, 3.3, 4.3,
        // 1.4, 2.4, 3.4, 4.4,
      };
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( ContinuousEnergyNeutron::TabularEquiprobableEnergyBins( 
          NBT, INT, energies, 4, outgoingTables ) );
      }
    }
  } // GIVEN
} // SCENARIO
