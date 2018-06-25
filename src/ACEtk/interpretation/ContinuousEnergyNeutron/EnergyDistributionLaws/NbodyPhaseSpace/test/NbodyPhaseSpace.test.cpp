#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Law66" ){
  GIVEN( "valid input values" ){
    int NPSX{ 10 };
    double Ap{ 3.14 };
    WHEN( "constructing a LAW66" ){
      ContinuousEnergyNeutron::NbodyPhaseSpace law66( NPSX, Ap );

      THEN( "the parameters can be verified" ){
        REQUIRE( NPSX == law66.numberBodies() );
        REQUIRE( NPSX == law66.NPSX() );

        REQUIRE( Ap == law66.totalMassRatio() );
        REQUIRE( Ap == law66.Ap() );
      }
    }
  } // GIVEN valid

  GIVEN( "invalid input values" ){
    int NPSX{ 10 };
    double Ap{ -0.1 };
    WHEN( "constructing a LAW66" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( ContinuousEnergyNeutron::NbodyPhaseSpace( NPSX, Ap ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO
