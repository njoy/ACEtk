#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

extern njoy::ACEtk::Table ACETable;

SCENARIO( "Finding Crosssections in a Table" ){
  GIVEN( "valid indices" ){
    std::vector< int > indices{ 0, 1, 45 };

    THEN( "a CrossSection can be created" ){
      for( auto& index : indices ){
        njoy::Log::info( "index: {}", index );
        REQUIRE_NOTHROW( nc::makeCrossSection( ACETable, index ) );
      }
    }
  } // GIVEN
  GIVEN( "invalid identifiers" ){
    std::vector< int > indices { -1, 49, 100 };
    THEN( "an exception is thrown" ){
      for( auto& index : indices ){
        njoy::Log::info( "index: {}", index );
        REQUIRE_THROWS( nc::makeCrossSection( ACETable, index ) );
      }
    }
  }
} // SCENARIO
