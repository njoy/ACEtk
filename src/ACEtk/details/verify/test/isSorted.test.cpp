
#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details;

SCENARIO( "Testing sorted verification" ){
  GIVEN( "sorted containers" ){
    std::vector< double > strictlyPositive{ 1.0, 2.0, 3.0 };
    std::vector< double > positive{ 0.0, 1.0, 2.0, 3.0 };
    std::vector< int > negative{ -1, 0, 2, 4 };

    THEN( "they all verify as sorted" ){
      REQUIRE_NOTHROW( verify::isSorted( strictlyPositive ) );
      REQUIRE_NOTHROW( verify::isSorted( positive ) );
      REQUIRE_NOTHROW( verify::isSorted( negative ) );
    }

    WHEN( "testing for positive values" ){
      REQUIRE(     verify::isSortedPositive( strictlyPositive ) );
      REQUIRE(     verify::isSortedPositive( positive ) );
      REQUIRE( not verify::isSortedPositive( negative ) );
    }
    WHEN( "testing for strictly positive values" ){
      REQUIRE(     verify::isSortedStrictlyPositive( strictlyPositive ) );
      REQUIRE( not verify::isSortedStrictlyPositive( positive ) );
      REQUIRE( not verify::isSortedStrictlyPositive( negative ) );
    }
  }

  GIVEN( "unsorted containers" ){
    std::vector< double > unsortedVector{ 1.0, 3.0, 2.0 };

    REQUIRE_THROWS( verify::isSorted( unsortedVector ) );
  }
} // SCENARIO
