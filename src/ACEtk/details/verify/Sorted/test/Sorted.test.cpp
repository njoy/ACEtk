#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details::verify;

SCENARIO( "Testing sorted verification" ){
  std::vector< double > strictlyPositive{ 1.0, 2.0, 3.0 };
  std::vector< double > positive{ 0.0, 1.0, 2.0, 3.0 };
  std::vector< int > negative{ -1, 0, 2, 4 };
  std::vector< double > unsortedVector{ 1.0, 3.0, 2.0 };

  GIVEN( "containers" ){
    WHEN( "constructing from initilizer list" ){
      REQUIRE_NOTHROW( Sorted< std::vector< int > >( { 1,2,3,4,5 } ) );

      REQUIRE_THROWS_AS( 
        Sorted< std::vector< double > >( { 1,2,3,2,1 } ), 
        UnsortedException 
      );
    }
    WHEN( "constructing from a 'range'" ){
      REQUIRE_NOTHROW( 
          Sorted< std::vector< double > >( strictlyPositive ) );
      REQUIRE_NOTHROW( 
          Sorted< std::vector< double > >( positive ) );
      REQUIRE_NOTHROW( 
          Sorted< std::vector< int > >( negative ) );
      REQUIRE_THROWS_AS( 
        Sorted< std::vector< double > >( unsortedVector ), 
        UnsortedException 
      );

    } // WHEN
    WHEN( "assigning" ){
      Sorted< std::vector< double > > sdVector = positive;
      REQUIRE_NOTHROW( 
          sdVector = Sorted< std::vector< double > >( strictlyPositive) );
      REQUIRE_THROWS_AS( 
        sdVector = unsortedVector,
        UnsortedException
      );
    }
  } // GIVEN

} // SCENARIO

