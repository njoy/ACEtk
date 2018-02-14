#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

extern njoy::ACEtk::Table ACETable;

SCENARIO( "Finding Crosssections in a Table" ){
  GIVEN( "valid identifiers" ){
    std::vector< int > IDs{ 16, 17, 102 };

    THEN( "a CrossSection can be created" ){
      for( auto& id : IDs ){
        REQUIRE_NOTHROW( nc::makeCrossSection( ACETable, id ) );
      }
    }
  } // GIVEN
  GIVEN( "invalid identifiers" ){

    THEN( "an exception is thrown" ){
      REQUIRE_THROWS( nc::makeCrossSection( ACETable, 2 ) );
    }
  }
} // SCENARIO
