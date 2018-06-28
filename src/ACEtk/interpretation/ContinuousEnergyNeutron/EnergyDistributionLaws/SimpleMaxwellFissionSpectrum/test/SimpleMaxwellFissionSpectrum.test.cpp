#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Law7" ){
  std::vector< double > NBT{ 1, 5 };
  std::vector< double > INT{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector< double > theta{ 0.1, 0.2, 0.3, 0.4, 0.5 };
  double restrictionEnergy{ 5.3 };
  
  GIVEN( "valid input values" ){
    WHEN( "constructing a LAW7" ){
      ContinuousEnergyNeutron::SimpleMaxwellFissionSpectrum law7(
        NBT, INT, energies, theta, restrictionEnergy );

      THEN( "the parameters can be verified" ){

        auto eip = law7.interpolationParameters();
        REQUIRE( ranges::equal( NBT, eip.NBT() ) );
        REQUIRE( ranges::equal( INT, eip.schemes() ) );
        REQUIRE( ranges::equal( energies, law7.incidentEnergies() ) );

        REQUIRE( ranges::equal( theta, law7.theta() ) );

        REQUIRE( restrictionEnergy == law7.restrictionEnergy() );
        REQUIRE( restrictionEnergy == law7.U() );
      }
    }
  } // GIVEN valid

  GIVEN( "invalid input values" ){
    WHEN( "theta is not the same size as the incident energies" ){
      std::vector< double > theta{ 0.1, 0.2, 0.3, 0.4 };
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( ContinuousEnergyNeutron::SimpleMaxwellFissionSpectrum(
                NBT, INT, energies, theta, restrictionEnergy ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO
