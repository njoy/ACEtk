
#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details;

SCENARIO( "Testing sorted verification" ){
  GIVEN( "sorted containers" ){
    std::vector< double > strictlyPositive{ 1.0, 2.0, 3.0 };
    std::vector< double > positive{ 0.0, 1.0, 2.0, 3.0 };
    std::vector< int > negative{ -1, 0, 2, 4 };

    THEN( "they all verify as sorted" ){
      REQUIRE( verify::sorted( strictlyPositive ) );
      REQUIRE( verify::sorted( positive ) );
      REQUIRE( verify::sorted( negative ) );
    }

    WHEN( "testing for positive values" ){
      REQUIRE( verify::sorted_positive( strictlyPositive ) );
      REQUIRE( verify::sorted_positive( positive ) );
      REQUIRE( not verify::sorted_positive( negative ) );
    }
    WHEN( "testing for strictly positive values" ){
      REQUIRE( verify::sorted_strictlyPositive( strictlyPositive ) );
      REQUIRE( not verify::sorted_strictlyPositive( positive ) );
      REQUIRE( not verify::sorted_strictlyPositive( negative ) );
    }
  }

  GIVEN( "unsorted containers" ){
    std::vector< double > unsortedVector{ 1.0, 3.0, 2.0 };

    REQUIRE( not verify::sorted( unsortedVector ) );
  }
} // SCENARIO
