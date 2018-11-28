#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details::verify;

SCENARIO( "Testing positivity verification" ){
  GIVEN( "containers" ){
    std::vector< double > strictlyPositive{ 1.0, 2.0, 3.0 };
    std::vector< double > posi{ 0.0, 1.0, 2.0, 3.0 };
    std::vector< int > negative{ -1, 0, 2, 4 };
    std::vector< double > unsortedVector{ 1.0, 3.0, 2.0 };
    
    WHEN( "constructing from initializer list" ){
      REQUIRE_NOTHROW( Positive< std::vector< int > >( { 1,2,3,4,5 } ) );

      REQUIRE_THROWS_AS( 
        Positive< std::vector< double > >( { 1,2,-13,2,1 } ), 
        exceptions::NotPositive& 
      );
    }
    WHEN( "constructing from a 'range'" ){
      REQUIRE_NOTHROW( Positive< std::vector< double > > ( strictlyPositive ) );
      REQUIRE_NOTHROW( Positive< std::vector< double > > ( posi ) );
      REQUIRE_NOTHROW( Positive< std::vector< double > > ( isPositive( posi ) ) );
      REQUIRE_NOTHROW( Positive< std::vector< double > > ( unsortedVector ) );
      REQUIRE_THROWS_AS(
        Positive< std::vector< int > >( negative ),
        exceptions::NotPositive&
      );

      WHEN( "constructing from a Sorted range" ){
        REQUIRE_NOTHROW( 
          Positive< Sorted< std::vector< double > > >( strictlyPositive ) );
        REQUIRE_NOTHROW( 
          Positive< Sorted< std::vector< double > > >( posi ) );
        REQUIRE_THROWS_AS(
          Positive< std::vector< int > > ( isSorted( negative ) ),
          exceptions::NotPositive&
        );
      }
      WHEN( "assigning" ){
        Positive< std::vector< double > > pdVector = strictlyPositive;
        REQUIRE_NOTHROW(
            pdVector = Positive< std::vector< double > >( posi ) );

            pdVector = { 1.0, 2.0, 6.0, 4.0 };
        CHECK( ranges::equal( { 1.0, 2.0, 6.0, 4.0 }, pdVector ) );

        REQUIRE_THROWS_AS(
            pdVector = Positive< std::vector< double > >( { 1, -2, 13, 2, 1 } ), 
            exceptions::NotPositive&
        );
      }
    } // WHEN
  } // GIVEN
} // SCENARIO
