#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO( "Creating a Reaction" ){
  GIVEN( "everything needed for a Reaction" ){
    std::vector< double > eGrid{1.0, 2.0, 3.0};
    std::vector< double > xsValues{2.1, 3.1, 4.1};
    auto xs =nc::CrossSection( eGrid, xsValues );

    double QValue{-3.14159265E-1};

    WHEN( "a Reaction is created" ){
      nc::Reaction reac( std::move( xs ), QValue );

      THEN( "the Q-value can be verified" ){
        REQUIRE( QValue == reac.QValue() );
      }

      THEN( "the CrossSection can be verified" ){
        auto XS = reac.crossSection();
        auto energyGrid = XS.energyGrid();
        auto xsBarns = XS.values();

        REQUIRE( xsValues.size() == xsBarns.size() );
        REQUIRE( eGrid.size() == energyGrid.size() );
        for( size_t i=0; i< eGrid.size(); i++ ){
          REQUIRE( eGrid[i]*dimwits::mega( dimwits::electronVolts) 
                   == energyGrid[i] );
          REQUIRE( xsValues[i]*dimwits::barn == xsBarns[i] );
        }
      }
    }
  } // GIVEN
} // SCENARIO
