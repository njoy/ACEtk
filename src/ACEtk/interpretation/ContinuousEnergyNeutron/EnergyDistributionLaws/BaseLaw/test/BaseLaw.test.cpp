#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Base secondary distribution Law" ){
  std::vector< double > NBT{ 1, 3 };
  std::vector< double > INT{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 3.0 };

  GIVEN( "valid input values" ){
    WHEN( "constructing a BaseLaw" ){
      ContinuousEnergyNeutron::BaseLaw base( NBT, INT, energies );

      THEN( "the parameters can be verified" ){
        auto eip = base.interpolationParameters();
        REQUIRE( ranges::equal( NBT, eip.NBT() ) );
        REQUIRE( ranges::equal( INT, eip.schemes() ) );
      }
    }
  } // GIVEN valid

  GIVEN( "invalid input values" ){
    WHEN( "wrong number of inerpolation regions" ){
      std::vector< double > NBT{ 1, 2, 3, 4, 5 };
      std::vector< double > INT{ 1, 2, 3, 4, 5 };
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( ContinuousEnergyNeutron::BaseLaw( 
          NBT, INT, energies ) );
      }
    }
    WHEN( "incident energies is wrong size" ){
      std::vector< double > energies{ 1.0, 2.0, 3.0, 4.0 };
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( 
            ContinuousEnergyNeutron::BaseLaw( NBT, INT, energies ) );
      }
    }
    WHEN( "NBT.back() doesn't match the number of energies" ){
      std::vector< double > NBT{ 1, 6 };
        THEN( "an exception is thrown" ){
          REQUIRE_THROWS( 
              ContinuousEnergyNeutron::BaseLaw( NBT, INT, energies ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO
