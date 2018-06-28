#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;
using namespace dimwits;

SCENARIO( "Law9" ){
  std::vector< double > NBT{ 1, 5 };
  std::vector< double > INT{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector< double > theta{ 0.1, 0.2, 0.3, 0.4, 0.5 };
  double restrictionEnergy{ 5.3 };
  
  GIVEN( "valid input values" ){
    WHEN( "constructing a LAW9" ){
      ContinuousEnergyNeutron::EvaporationSpectrum law9(
        NBT, INT, energies, theta, restrictionEnergy );

      THEN( "the parameters can be verified" ){

        auto eip = law9.interpolationParameters();
        REQUIRE( ranges::equal( NBT, eip.NBT() ) );
        REQUIRE( ranges::equal( INT, eip.schemes() ) );

        auto refEnergies = scaleBy( 1.0*mega( electronVolts ) )( energies );
        REQUIRE( ranges::equal( refEnergies, law9.incidentEnergies() ) );

        REQUIRE( ranges::equal( theta, law9.theta() ) );

        REQUIRE( restrictionEnergy == law9.restrictionEnergy() );
        REQUIRE( restrictionEnergy == law9.U() );
      }
    }
  } // GIVEN valid

  GIVEN( "invalid input values" ){
    WHEN( "theta is not the same size as the incident energies" ){
      std::vector< double > theta{ 0.1, 0.2, 0.3, 0.4 };
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( ContinuousEnergyNeutron::EvaporationSpectrum(
                NBT, INT, energies, theta, restrictionEnergy ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO
