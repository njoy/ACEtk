#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details::verify;

SCENARIO( "Testing sorted verification" ){
  GIVEN( "containers" ){
    std::vector< double > increasing{ 0.1, 0.4, 0.6, 1.0 };
    std::vector< double > negative{ -0.1, 0.4, 0.6, 1.0 };
    std::vector< double > unsortedVector{ 1.0, 3.0, 2.0, 4.0 };

    WHEN( "constructing from initializer list" ){
      CHECK_NOTHROW( CDF< std::vector< double > >( { 1.0, 2.0, 3.0 } ) );
      CHECK_THROWS_AS(
        CDF< std::vector< double > >( { 1.0, 3.0, 2.0 } ),
        exceptions::InvalidCDF&
      );
    }

    WHEN( "constructing from a range" ){
      CHECK_NOTHROW( CDF< std::vector< double > >( increasing ) );
      CHECK_THROWS_AS( 
          CDF< std::vector< double > >( negative ),
          exceptions::InvalidCDF&
      );
      CHECK_THROWS_AS( 
          CDF< std::vector< double > >( unsortedVector ),
          exceptions::InvalidCDF&
      );
    }
    WHEN( "assigning" ){
      CDF< std::vector< double > > cdf = increasing;

      std::vector< double > newCDF{ 0.3, 0.6, 0.6, 1.0 };
      cdf = CDF< std::vector< double > >( njoy::utility::copy( newCDF ) );

      for( size_t i=0; i< newCDF.size(); i++ ){
        CHECK( newCDF[ i ] == cdf[ i ] );
      }
      // CHECK( ranges::equal( newCDF, cdf ) );

      CHECK_THROWS_AS(
        cdf = unsortedVector,
        exceptions::InvalidCDF&
      );
    }
  } // GIVEN
} // SCENARIO
