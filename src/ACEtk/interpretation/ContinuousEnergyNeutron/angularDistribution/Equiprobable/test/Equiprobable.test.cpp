#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO( "Constructing an equiprobable bins for angular distribution" ){
  GIVEN( "a list of energies and bin boundaries" ){
    std::vector< double > eGrid{1.0, 2.0, 3.0};
    std::vector< double > boundaries( 33 );
    std::iota( boundaries.begin(), boundaries.end(), 1 );

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
      boundaries.push_back( 45.0 );
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( interpretation::nc::angularDistribution::Equiprobable(
                eGrid, boundaries ) );
      }
    }
  }
} // SCENARIO
