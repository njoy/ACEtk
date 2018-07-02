
#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details;

SCENARIO( "Testing positive verification" ){
  GIVEN( "containers" ){
    std::vector< double > strictlyPositive{ 1.0, 2.0, 3.0 };
    std::vector< double > positive{ 0.0, 1.0, 2.0, 3.0 };
    std::vector< int > negative{ -1, 0, 2, 4 };

    WHEN( "testing for positivity" ){
      REQUIRE( verify::positive( strictlyPositive ) );
      REQUIRE( verify::positive( positive ) );
      REQUIRE( not verify::positive( negative ) );
    }

    WHEN( "testing for strict positivity" ){
      REQUIRE( verify::strictlyPositive( strictlyPositive ) );
      REQUIRE( not verify::strictlyPositive( positive ) );
      REQUIRE( not verify::strictlyPositive( negative ) );
    }
  } // GIVEN positive
} // SCENARIO
