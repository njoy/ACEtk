#define CATCH_CONFIG_MAIN

#include <iostream>
#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "SecondaryDistribution" ){
  int INTT{ 2 };
  std::vector< double > PDF{ 0.1, 0.2, 0.3, 0.3, 0.1 };
  std::vector< double > CDF{ 0.1, 0.3, 0.6, 0.9, 1.0 };
  std::vector< double > energies{ 1.0, 2.0, 3.0, 4.0, 5.0 };
  GIVEN( "valid input values" ){

    WHEN( "the Distribution is constructed" ){
      ContinuousEnergyNeutron::SecondaryDistribution dist{ 
        INTT, energies, PDF, CDF };

      THEN( "the values can be verified" ){
        REQUIRE( INTT == dist.interpolationParameter() );

        REQUIRE( ranges::equal( energies, dist.energyGrid() ) );

        REQUIRE( ranges::equal( PDF, dist.PDF() ) );
        REQUIRE( ranges::equal( CDF, dist.CDF() ) );

      }
    }
  } // GIVEN valid

  GIVEN( "invalid input values" ){
    WHEN( "wrong number of energies is given" ){
      std::vector< double > energies{ 1.0, 2.0, 3.0, 4.0 };

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( 
          ContinuousEnergyNeutron::SecondaryDistribution(
            INTT, energies, PDF, CDF ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO

