#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Law11" ){
  std::vector< double > aNBT{ 1, 3 };
  std::vector< double > aINT{ 2, 1 };
  std::vector< double > aEnergies{ 1.0, 2.0, 3.0 };
  std::vector< double > aValues{ 10.0, 11.0, 12.0 };

  std::vector< double > bNBT{ 1, 4 };
  std::vector< double > bINT{ 2, 1 };
  std::vector< double > bEnergies{ 1.0, 2.0, 3.0, 4.0 };
  std::vector< double > bValues{ 20.0, 21.0, 22.0, 23.0 };

  GIVEN( "valid input parameters" ){
    WHEN( "constructing a LAW11" ){
      ContinuousEnergyNeutron::EnergyDependentWattSpectrum law11(
        aNBT, aINT, aEnergies, aValues, bNBT, bINT, bEnergies, bValues );
      THEN( "the parameters can be verified" ){
        auto a_eip = law11.aInterpolationParameters();
        REQUIRE( ranges::equal( aNBT, a_eip.NBT() ) );
        REQUIRE( ranges::equal( aINT, a_eip.schemes() ) );
        REQUIRE( ranges::equal( aEnergies, law11.aEnergies() ) );
        REQUIRE( ranges::equal( aValues, law11.a() ) );

        auto b_eip = law11.bInterpolationParameters();
        REQUIRE( ranges::equal( bNBT, b_eip.NBT() ) );
        REQUIRE( ranges::equal( bINT, b_eip.schemes() ) );
        REQUIRE( ranges::equal( bEnergies, law11.bEnergies() ) );
        REQUIRE( ranges::equal( bValues, law11.b() ) );

      }
    }
  } // GIVEN valid

  GIVEN( "invalid input parameters" ){
    WHEN( "wrong number of aValues is given" ){
      std::vector< double > aValues{ 10.0, 11.0, 12.0, 13.0 };
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS(
          ContinuousEnergyNeutron::EnergyDependentWattSpectrum(
            aNBT, aINT, aEnergies, aValues, bNBT, bINT, bEnergies, bValues ) );
      }
    }
    WHEN( "wrong number of bValues is given" ){
      std::vector< double > bValues{ 10.0, 11.0, 12.0 };
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS(
          ContinuousEnergyNeutron::EnergyDependentWattSpectrum(
            aNBT, aINT, aEnergies, aValues, bNBT, bINT, bEnergies, bValues ) );
      }
    }
    WHEN( "wrong number of aEnergies is given" ){
      std::vector< double > aEnergies{ 10.0, 11.0, 12.0, 13.0 };
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS(
          ContinuousEnergyNeutron::EnergyDependentWattSpectrum(
            aNBT, aINT, aEnergies, aValues, bNBT, bINT, bEnergies, bValues ) );
      }
    }
    WHEN( "wrong number of bEnergies is given" ){
      std::vector< double > bEnergies{ 10.0, 11.0, 12.0 };
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS(
          ContinuousEnergyNeutron::EnergyDependentWattSpectrum(
            aNBT, aINT, aEnergies, aValues, bNBT, bINT, bEnergies, bValues ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO
