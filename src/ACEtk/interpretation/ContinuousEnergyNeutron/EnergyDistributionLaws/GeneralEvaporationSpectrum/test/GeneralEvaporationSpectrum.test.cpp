#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Law5" ){
  std::vector< double > NBT{ 1, 5 };
  std::vector< double > INT{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector< double > theta{ 0.1, 0.2, 0.3, 0.4, 0.5 };
  std::vector< double > X{ 1/3, 2/3, 3/3 };
  GIVEN( "valid input parameters" ){
    WHEN( "constructing a LAW5" ){
      ContinuousEnergyNeutron::GeneralEvaporationSpectrum law5(
      NBT, INT, energies, theta, X );

      THEN( "the parameters can be verified" ){

        auto eip = law5.interpolationParameters();
        REQUIRE( ranges::equal( NBT, eip.NBT() ) );
        REQUIRE( ranges::equal( INT, eip.schemes() ) );
        REQUIRE( ranges::equal( energies, law5.incidentEnergies() ) );

        REQUIRE( ranges::equal( theta, law5.theta() ) );
        REQUIRE( ranges::equal( X, law5.tabulatedProbabilisticFunction() ) );
        REQUIRE( ranges::equal( X, law5.X() ) );
      }
    }
  } // GIVEN valid
  GIVEN( "invalid input parameters" ){
    WHEN( "theta is not the same size as the incident energies" ){
      std::vector< double > theta{ 0.1, 0.2, 0.3, 0.4 };
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( ContinuousEnergyNeutron::GeneralEvaporationSpectrum(
                NBT, INT, energies, theta, X ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO
