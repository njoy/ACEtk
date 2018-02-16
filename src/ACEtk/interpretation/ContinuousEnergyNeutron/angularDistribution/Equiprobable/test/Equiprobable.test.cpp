#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO( "Constructing an equiprobable bins for angular distribution" ){
  GIVEN( "a list of energies and bin boundaries" ){
    std::vector< double > eGrid{1.0, 2.0, 3.0};
    std::vector< double > bins( 33 );
    std::iota( bins.begin(), bins.end(), 1 );

    std::vector< std::optional< std::vector< double > > > boundaries{ 
      bins, std::nullopt, bins };
    WHEN( "constructing a Tabulated representation" ){
      interpretation::nc::angularDistribution::Equiprobable equi( 
          eGrid, boundaries );

      THEN( "the boundaries and energies can be verified" ){
        bool equal = ranges::equal( 
            scaleBy( 1.0*mega( electronVolts ) )( eGrid ),
            equi.energyGrid() );
        REQUIRE( equal );

        equal = ranges::equal( boundaries, equi.boundaries() );
        REQUIRE( ranges::equal( boundaries, equi.boundaries() ) );
      }
    }

    WHEN( "the length of the boundaries is not 33" ){
      boundaries[0]->push_back( 45.0 );
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( interpretation::nc::angularDistribution::Equiprobable(
                eGrid, boundaries ) );
      }
    }
    WHEN( "there are not enough bin boundaries" ){
      boundaries.pop_back();
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( interpretation::nc::angularDistribution::Equiprobable(
                eGrid, boundaries ) );
      }
    }
    WHEN( "there are too many bin boundaires" ){
      boundaries.push_back( bins );
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( interpretation::nc::angularDistribution::Equiprobable(
                eGrid, boundaries ) );
      }
    }
  }
} // SCENARIO
