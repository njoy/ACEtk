
#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details;

SCENARIO( "Testing positive verification" ){
  GIVEN( "sorted containers" ){
    std::vector< double > strictlyPositive{ 1.0, 2.0, 3.0 };
    std::vector< double > positive{ 0.0, 1.0, 2.0, 3.0 };
    std::vector< int > negative{ -1, 0, 2, 4 };

    WHEN( "testing for positivity" ){
      REQUIRE( verify::isPositive( verify::isSorted( strictlyPositive ) ) );
      REQUIRE( verify::isPositive( verify::isSorted( positive ) ) );
      REQUIRE( not verify::isPositive( verify::isSorted( negative ) ) );
    }

    WHEN( "testing for strict positivity" ){
      REQUIRE( 
          verify::isStrictlyPositive( verify::isSorted( strictlyPositive ) ) );
      REQUIRE( not verify::isStrictlyPositive( verify::isSorted( positive ) ) );
      REQUIRE( not verify::isStrictlyPositive( verify::isSorted( negative ) ) );
    }
  } // GIVEN sorted

  GIVEN( "unsorted containers" ){
    std::vector< double > strictlyPositive{ 4.0, 2.0, 3.0 };
    std::vector< double > positive{ 0.0, 1.0, 7.0, 3.0 };
    std::vector< int > negative{ -1, 0, 2, 4 };

    WHEN( "testing for positivity" ){
      REQUIRE( verify::isPositive( strictlyPositive ) );
      REQUIRE( verify::isPositive( positive ) );
      REQUIRE( not verify::isPositive( negative ) );
    }

    WHEN( "testing for strict positivity" ){
      REQUIRE( verify::isStrictlyPositive( strictlyPositive ) );
      REQUIRE( not verify::isStrictlyPositive( positive ) );
      REQUIRE( not verify::isStrictlyPositive( negative ) );
    }
  } // GIVEN positive
} // SCENARIO
