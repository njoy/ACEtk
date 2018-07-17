
#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details;

SCENARIO( "Testing positive verification" ){
  GIVEN( "sorted containers" ){
    std::vector< double > strictlyPositive{ 1.0, 2.0, 3.0 };
    std::vector< double > positive{ 0.0, 1.0, 2.0, 3.0 };
    std::vector< int > negative{ -1, 0, 2, 4 };

    WHEN( "testing for positivity" ){
      REQUIRE_NOTHROW( verify::isPositive( verify::isSorted( strictlyPositive ) ) );
      REQUIRE_NOTHROW( verify::isPositive( verify::isSorted( positive ) ) );
      REQUIRE_THROWS( verify::isPositive( verify::isSorted( negative ) ) );
    }

    WHEN( "testing for strict positivity" ){
      REQUIRE_NOTHROW( 
          verify::isStrictlyPositive( verify::isSorted( strictlyPositive ) ) );
      REQUIRE_THROWS( verify::isStrictlyPositive( verify::isSorted( positive ) ) );
      REQUIRE_THROWS( verify::isStrictlyPositive( verify::isSorted( negative ) ) );
    }
  } // GIVEN sorted

  GIVEN( "unsorted containers" ){
    std::vector< double > strictlyPositive{ 4.0, 2.0, 3.0 };
    std::vector< double > positive{ 0.0, 1.0, 7.0, 3.0 };
    std::vector< int > negative{ -1, 0, 2, 4 };

    WHEN( "testing for positivity" ){
      REQUIRE( verify::isPositive( strictlyPositive ) );
      REQUIRE( verify::isPositive( positive ) );
      REQUIRE_THROWS( verify::isPositive( negative ) );
    }

    WHEN( "testing for strict positivity" ){
      REQUIRE( verify::isStrictlyPositive( strictlyPositive ) );
      REQUIRE_THROWS( verify::isStrictlyPositive( positive ) );
      REQUIRE_THROWS( verify::isStrictlyPositive( negative ) );
    }
  } // GIVEN positive
} // SCENARIO
