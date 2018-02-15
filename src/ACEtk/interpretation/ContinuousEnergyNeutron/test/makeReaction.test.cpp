#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

extern njoy::ACEtk::Table ACETable;

SCENARIO( "Making reactions" ){
  GIVEN( "valid identifiers (MT numbers)" ){
    std::vector< int > IDs{ 16, 17, 102 };
    WHEN( "a reaction is created" ){
      for( auto& id : IDs ){
        njoy::Log::info( "id: {}", id );
        REQUIRE_NOTHROW( nc::makeReaction( ACETable, id ) );
      }
    }
  } // GIVEN

  GIVEN( "invalid identifiers (MT numbers)" ){
    std::vector< int > IDs{ 1, 6, 4004 };
    WHEN( "a Reaction is created" ){
      THEN( "an exception is thrown" ){
        for( auto& id : IDs ){
          njoy::Log::info( "id: {}", id );
          REQUIRE_THROWS( nc::makeReaction( ACETable, id ) );
        }
      }
    }
  } // GIVEN
} // SCENARIO
