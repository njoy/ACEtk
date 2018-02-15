#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO( "Finding reaction indices" ){
  GIVEN( "list of reaciton IDs" ){
    std::vector<int> IDs{{
      16, 17, 18, 37, 51, 52, 53, 54, 55, 56, 57, 58, 59, 
      60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 
      73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 
      86, 87, 88, 89, 90, 91, 102, 444}};

    WHEN( "giving valid IDs" ){
      THEN( "the indices can be found" ){

        REQUIRE( 3 == nc::reactionIndex( IDs, 37 ) );

        for( size_t i=0; i < IDs.size(); i++ ){
          REQUIRE( i == nc::reactionIndex( IDs, IDs[i] ) );
        }
      }
    } // WHEN
    WHEN( "given invalid IDs" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( nc::reactionIndex( IDs, 15 ) );
      }
    }
  } // GIVEN
} // SCENARIO
