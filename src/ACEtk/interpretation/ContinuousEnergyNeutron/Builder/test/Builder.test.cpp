#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Complete ContinuousEnergyNeutron::Builder" ){
  ContinuousEnergyNeutron::Builder nc{};

  GIVEN( "valid data" ){
    nc.header()
         .processDate( date::year{2019}/3/14 )
         .temperature( 2.5301E-8*dimwits::mega( electronVolts ) )
         .atomicWeightRatio( 0.99173 )
         .zaid( "1001.123nc" )
      .add(); // header
  } // GIVEN valid
  GIVEN( "invalid data" ){
  } // GIVEN invalid
} // SCENARIO complete

SCENARIO( "Testing ContinuousEnergyNeutron::Builder" ){
  ContinuousEnergyNeutron::Builder ncBuilder{};

  GIVEN( "valid data for the energy grid" ){
    std::vector< double > grid{ 1.0, 2.0, 3.0, 4.0, 5.0 };
    ncBuilder.energyGrid( njoy::utility::copy( grid ) );

    THEN( "we can verify the energy grid" ){
      CHECK( ranges::equal( grid, ncBuilder.energyGrid() ) );
    }
  } // GIVEN valid

  GIVEN( "invalid data" ){
    WHEN( "the energy grid has negative components" ){
      std::vector< double > grid{1.0, 2.0, 3.0, -4.0, 5.0};
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          ncBuilder.energyGrid( njoy::utility::copy( grid ) ),
          details::verify::exceptions::NotPositive&
          );
      }
    }
    WHEN( "the energy grid is not sorted " ){
      std::vector< double > grid{1.0, 2.0, 3.0, 7.0, 5.0};
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          ncBuilder.energyGrid( njoy::utility::copy( grid ) ),
          details::verify::exceptions::Unsorted&
          );
      }
    }
    WHEN( "no energy grid has been given" ){
      THEN( "an exception is thrown when the energy grid is asked for" ){
        CHECK_THROWS( ncBuilder.energyGrid() );
      }
    }
  }
} // SCENARIO
