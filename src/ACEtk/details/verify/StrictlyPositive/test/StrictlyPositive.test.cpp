#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details::verify;

SCENARIO( "Testing positivity verification" ){
  GIVEN( "containers" ){
    std::vector< double > strictPosi{ 1.0, 2.0, 3.0 };
    std::vector< double > posi{ 0.0, 1.0, 2.0, 3.0 };
    std::vector< int > negative{ -1, 0, 2, 4 };
    std::vector< double > unsortedVector{ 1.0, 3.0, 2.0 };
    
    WHEN( "constructing from initializer list" ){
      REQUIRE_NOTHROW( 
          StrictlyPositive< std::vector< int > >( { 1,2,3,4,5 } ) );

      REQUIRE_THROWS_AS( 
        StrictlyPositive< std::vector< double > >( { 1,2,-13,2,1 } ), 
        exceptions::NotStrictlyPositive&
      );

      REQUIRE_THROWS_AS( 
        StrictlyPositive< std::vector< double > >( { 1,0,13,2,1 } ), 
        exceptions::NotStrictlyPositive&
      );
    }
    WHEN( "constructing from a 'range'" ){
      REQUIRE_NOTHROW( 
        StrictlyPositive< std::vector< double > > ( strictPosi ) );
      REQUIRE_THROWS_AS( 
        StrictlyPositive< std::vector< double > > ( posi ),
        exceptions::NotStrictlyPositive&
      );
      REQUIRE_THROWS_AS( 
        StrictlyPositive< std::vector< double > > ( positive( posi ) ),
        exceptions::NotStrictlyPositive&
      );
      REQUIRE_NOTHROW( 
        StrictlyPositive< std::vector< double > > ( unsortedVector ) );
      REQUIRE_THROWS_AS(
        StrictlyPositive< std::vector< int > >( negative ),
        exceptions::NotStrictlyPositive&
      );

      WHEN( "constructing from a Sorted range" ){
        REQUIRE_NOTHROW( 
          StrictlyPositive< Sorted< std::vector< double > > >( 
              strictPosi ) );
        REQUIRE_THROWS_AS( 
          StrictlyPositive< Sorted< std::vector< double > > >( posi ),
          exceptions::NotStrictlyPositive&
        );
        REQUIRE_THROWS_AS(
          StrictlyPositive< std::vector< int > > ( sorted( negative ) ),
          exceptions::NotStrictlyPositive&
        );
      }
      WHEN( "assigning" ){
        StrictlyPositive< std::vector< double > > pdVector = strictPosi;
        REQUIRE_THROWS_AS(
            pdVector = StrictlyPositive< std::vector< double > >( posi ),
            exceptions::NotStrictlyPositive&
        );

            pdVector = { 1.0, 2.0, 6.0, 4.0 };
        //CHECK( ranges::equal( { 1.0, 2.0, 6.0, 4.0 }, pdVector ) );

        REQUIRE_THROWS_AS(
            pdVector = StrictlyPositive< std::vector< double > >( 
                { 1, -2, 13, 2, 1 } ), 
            exceptions::NotStrictlyPositive&
        );
      }
    } // WHEN
  } // GIVEN
} // SCENARIO

