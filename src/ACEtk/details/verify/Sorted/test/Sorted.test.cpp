#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details;

SCENARIO( "Testing sorted verification" ){
  GIVEN( "sorted containers" ){
    std::vector< double > strictlyPositive{ 1.0, 2.0, 3.0 };
    std::vector< double > positive{ 0.0, 1.0, 2.0, 3.0 };
    std::vector< int > negative{ -1, 0, 2, 4 };

    THEN( "they all verify as sorted" ){
      REQUIRE_NOTHROW( 
          verify::Sorted< std::vector< double > >( strictlyPositive ) );
      REQUIRE_NOTHROW( 
          verify::Sorted< std::vector< double > >( positive ) );
      REQUIRE_NOTHROW( 
          verify::Sorted< std::vector< int > >( negative ) );
    }
  }

  GIVEN( "unsorted containers" ){
    std::vector< double > unsortedVector{ 1.0, 3.0, 2.0 };

    REQUIRE_THROWS( verify::Sorted< std::vector< double > >( unsortedVector ) );
  }
}

