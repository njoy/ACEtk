#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details::verify;

SCENARIO( "Testing sorted verification" ){
  std::vector< double > strictlyPositive{ 1.0, 2.0, 3.0 };
  std::vector< double > positive{ 0.0, 1.0, 2.0, 3.0 };
  std::vector< int > negative{ -1, 0, 2, 4 };
  std::vector< double > unsortedVector{ 1.0, 3.0, 2.0 };

  GIVEN( "sorted containers" ){
    THEN( "they all verify as sorted" ){
      // REQUIRE_NOTHROW( Sorted< std::vector< double > >{ 1.1, 1.2, 1.3 } );
      REQUIRE_NOTHROW( 
          Sorted< std::vector< double > >( strictlyPositive ) );
      REQUIRE_NOTHROW( 
          Sorted< std::vector< double > >( positive ) );
      REQUIRE_NOTHROW( 
          Sorted< std::vector< int > >( negative ) );
    }
    WHEN( "assigning to Sorted" ){
      // Sorted< std::vector< int > > sortedDouble{ 1.1, 1.2, 1.3 };
      // std::vector< double > sortedDouble{ 1.1, 1.2, 1.3 };
    }
  } // GIVEN

  GIVEN( "unsorted containers" ){
    THEN( "an exception is thrown" ){
      REQUIRE_THROWS_AS( 
        Sorted< std::vector< double > >( unsortedVector ), 
        UnsortedException );
    }
  } // GIVEN
} // SCENARIO

