#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

nc::CrossSection makeXS();

SCENARIO( "Creating a Reaction" ){
  GIVEN( "a CrossSection" ){
    auto xs = makeXS();

    WHEN( "a Reaction is created" ){
      nc::Reaction reac( std::move( xs ) );
    }
  } // GIVEN
} // SCENARIO

nc::CrossSection makeXS(){
    std::vector< double > eGrid{1.0, 2.0, 3.0};
    std::vector< double > xsValues{2.1, 3.1, 4.1};

    return nc::CrossSection( eGrid, xsValues );

}
