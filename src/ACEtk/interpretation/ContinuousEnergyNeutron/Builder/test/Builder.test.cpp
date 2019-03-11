#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing ContinuousEnergyNeutron::Builder" ){
  ContinuousEnergyNeutron::Builder ncBuilder{};

  GIVEN( "data for the energy grid" ){
    std::vector< double > grid{ 1.0, 2.0, 3.0, 4.0, 5.0 };
    ncBuilder.energyGrid( njoy::utility::copy( grid ) );

    THEN( "we can verify the energy grid" ){
      CHECK( ranges::equal( grid, ncBuilder.energyGrid() ) );
    }

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
  }
  WHEN( "no energy grid has been given" ){
    THEN( "an exception is thrown when the energy grid is asked for" ){
      CHECK_THROWS( ncBuilder.energyGrid() );
    }
  }
} // SCENARIO
