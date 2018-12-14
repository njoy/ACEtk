#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details::verify;

SCENARIO( "Testing sorted verification" ){
  GIVEN( "containers" ){
    std::vector< double > normal{ 0.1, 0.3, 0.5, 0.1 };
    std::vector< double > austin{ -0.1, 0.4, 0.6, 1.0 };
    std::vector< double > wim{ 0.1, 0.4, 0.6, 1.0 };

    WHEN( "constructing from initializer list" ){
      CHECK_NOTHROW( Normal< std::vector< double > >( { 0.1, 0.2, 0.7 } ) );
      CHECK_THROWS_AS(
        Normal< std::vector< double > >( { 1.0, 3.0, 2.0 } ),
        exceptions::NotNormal&
      );
    }

    WHEN( "constructing from a range" ){
      CHECK_NOTHROW( Normal< std::vector< double > >( njoy::utility::copy( normal ) ) );
      CHECK_THROWS_AS( 
          Normal< std::vector< double > >( austin ),
          exceptions::NotNormal&
      );
      CHECK_THROWS_AS( 
          Normal< std::vector< double > >( wim ),
          exceptions::NotNormal&
      );
    }
    WHEN( "assigning" ){
      Normal< std::vector< double > > normed = normal;

      std::vector< double > newNorm{ 0.3, 0.2, 0.2, 0.3 };
      normed = Normal< std::vector< double > >( 
          njoy::utility::copy( newNorm) );

      for( size_t i=0; i< newNorm.size(); i++ ){
        CHECK( newNorm[ i ] == normed[ i ] );
      }
      // CHECK( ranges::equal( newNormal, normed ) );

      CHECK_THROWS_AS(
        normed = wim,
        exceptions::NotNormal&
      );
    }
  } // GIVEN
} // SCENARIO
