
#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details;

SCENARIO( "Testing positive verification" ){
  GIVEN( "containers" ){
    std::vector< double > strictlyPositive{ 1.0, 2.0, 3.0 };
    std::vector< double > positive{ 0.0, 1.0, 2.0, 3.0 };
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
