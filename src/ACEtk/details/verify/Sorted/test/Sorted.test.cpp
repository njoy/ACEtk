#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details::verify;

SCENARIO( "Testing sorted verification" ){
  GIVEN( "containers" ){
    std::vector< double > strictlyPositive{ 1.0, 2.0, 3.0 };
    std::vector< double > positive{ 0.0, 1.0, 2.0, 3.0 };
    std::vector< int > negative{ -1, 0, 2, 4 };
    std::vector< double > unsortedVector{ 1.0, 3.0, 2.0 };

    WHEN( "constructing from initializer list" ){
      REQUIRE_NOTHROW( Sorted< std::vector< int > >( { 1,2,3,4,5 } ) );

      REQUIRE_THROWS_AS( 
        Sorted< std::vector< double > >( { 1,2,3,2,1 } ), 
        exceptions::Unsorted &
      );
    }
    WHEN( "constructing from a 'range'" ){
      // REQUIRE_NOTHROW( Sorted< std::vector< double > >( 
      //         njoy::ACEtk::Table::slice( strictlyPositive ) ) );
      REQUIRE_NOTHROW( 
          Sorted< std::vector< double > >( strictlyPositive ) );
      REQUIRE_NOTHROW( 
          Sorted< std::vector< double > >( positive ) );
      REQUIRE_NOTHROW( 
          Sorted< std::vector< int > >( negative ) );
      REQUIRE_THROWS_AS( 
        Sorted< std::vector< double > >( unsortedVector ), 
        exceptions::Unsorted&
      );

    } // WHEN
    WHEN( "assigning" ){
      Sorted< std::vector< double > > sdVector = positive;
      REQUIRE_NOTHROW( 
          sdVector = Sorted< std::vector< double > >( strictlyPositive) );

      sdVector = { 1.0, 2.0, 3.0 };
      CHECK( ranges::equal( { 1.0, 2.0, 3.0 }, sdVector ) );

      REQUIRE_THROWS_AS( 
        sdVector = unsortedVector,
        exceptions::Unsorted&
      );
    }
  } // GIVEN

} // SCENARIO

