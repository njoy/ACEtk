#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details;

SCENARIO( "Testing positive verification" ){
  GIVEN( "sorted containers" ){
    std::vector< double > strictlyPositive{ 1.0, 2.0, 3.0 };
    std::vector< double > positive{ 0.0, 1.0, 2.0, 3.0 };
    std::vector< int > negative{ -1, 0, 2, 4 };

    THEN( "they all verify as positive" ){
      REQUIRE_NOTHROW( 
          verify::Positive< std::vector< double > >( 
              verify::Sorted< std::vector< double > >( strictlyPositive ) ) );
      REQUIRE_NOTHROW( 
          verify::Positive< std::vector< double > >( positive ) );
      REQUIRE_THROWS( 
          verify::Positive< std::vector< int > >( negative ) );
    } 
  } // GIVEN sorted

  GIVEN( "unsorted containers" ){
    std::vector< double > strictlyPositive{ 4.0, 2.0, 3.0 };
    std::vector< double > positive{ 0.0, 1.0, 7.0, 3.0 };
    std::vector< int > negative{ 1, 0, -2, 4 };

    WHEN( "testing for positivity" ){
      REQUIRE_NOTHROW( 
          verify::Positive< std::vector< double > >( strictlyPositive ) );
      REQUIRE_NOTHROW( 
          verify::Positive< std::vector< double > >( positive ) );
      REQUIRE_THROWS( 
          verify::Positive< std::vector< int > >( negative ) );
    } 
  } // GIVEN unsorted
} // SCENARIO
