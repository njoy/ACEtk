#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Law2" ){
  GIVEN( "valid LP and EG values" ){
    double EG{ 3.14 };
    std::vector< int > validLPs{ 0, 1, 2 };

    WHEN( "constructing DiscretePhotonEnergy" ){
      THEN( "the parameters can be verified" ){
        for( auto LP : validLPs ){
          ContinuousEnergyNeutron::DiscretePhotonEnergy law2( LP, EG );
          REQUIRE( 3.14 == law2.photonEnergy() );
          REQUIRE( LP == law2.primaryFlag() );
        }
      }
    }
  } //GIVEN
  GIVEN( "invalid LP values" ){
    double EG{ 3.14 };
    std::vector< int > invalidLPs{ -1, 3 };

    WHEN( "constructing DiscretePhotonEnergy" ){
      THEN( "an exception is thrown" ){
        for( auto LP : invalidLPs ){
          REQUIRE_THROWS( 
            ContinuousEnergyNeutron::DiscretePhotonEnergy( LP, EG ) );
        }
      }
    }
  }
} // SCENARIO
