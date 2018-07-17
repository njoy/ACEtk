#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Constructing an equiprobable bins for angular distribution" ){
  GIVEN( "a list of bin boundaries" ){
    std::vector< double > boundaries; boundaries.resize( 33 );

    WHEN( "boundaries are correct" ){
      for( size_t i=0; i < boundaries.size(); i++ ){
        boundaries[i] = -1.0 + i*( 2.0/32 );
      }
      ContinuousEnergyNeutron::angularDistribution::Equiprobable equi( 
          boundaries );

      THEN( "the boundaries can be verified" ){
        bool equal = ranges::equal( boundaries, equi.boundaries() );
        REQUIRE( ranges::equal( boundaries, equi.boundaries() ) );
      }
    }
    WHEN( "boundaries are incorrect" ){
      for( size_t i=0; i < boundaries.size(); i++ ){
        boundaries[i] = -1.0 + i*( 2.0/32 );
      }
      WHEN( "first value is != -1.0" ){
        boundaries.front() = -0.99;

        THEN( "an exception is thrown" ){
          // REQUIRE_THROWS( 
          //   ContinuousEnergyNeutron::angularDistribution::Equiprobable( 
          //       boundaries ) );
        }
      }
      WHEN( "last value is != 1.0" ){
        boundaries.back() = 0.99;

        THEN( "an exception is thrown" ){
          // REQUIRE_THROWS( 
          //   ContinuousEnergyNeutron::angularDistribution::Equiprobable( 
          //       boundaries ) );
        }
      }
      WHEN( "last values are not sorted" ){
        boundaries[1] = 4.0/32;

        THEN( "an exception is thrown" ){
          // REQUIRE_THROWS( 
          //   ContinuousEnergyNeutron::angularDistribution::Equiprobable( 
          //       boundaries ) );
        }
      }
    }
  }
} // SCENARIO
