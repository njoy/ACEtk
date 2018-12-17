#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details::verify;

SCENARIO( "Testing sorted verification" ){
  GIVEN( "containers" ){
    std::vector< double > cosineBins{ -1.0, -0.5, 0.0, 0.5, 1.0 };
    std::vector< double > unsorted{ 1.0, 0.5, 0.0, -0.5, -1.0 };
    std::vector< double > invalid{ -1.01, 1.01 };

    WHEN( "constructing from initializer list" ){
      CHECK_NOTHROW( CosineBins< std::vector< double > >( { 0.1, 0.2, 0.3 } ) );
      CHECK_THROWS_AS(
        CosineBins< std::vector< double > >( { 1.0, 3.0, 2.0 } ),
        exceptions::InvalidCosine&
      );
    }

    WHEN( "constructing from a range" ){
      CHECK_NOTHROW( CosineBins< std::vector< double > >( cosineBins ) );
      CHECK_THROWS_AS(
        CosineBins< std::vector< double > >( unsorted ),
        exceptions::Unsorted&
      );
      CHECK_THROWS_AS(
        CosineBins< std::vector< double > >( invalid ),
        exceptions::InvalidCosine&
      );
    }
    WHEN( "assigning" ){
      CosineBins< std::vector< double > > bins = cosineBins;
      std::vector< double > newBins{ -1, .3, 1 };
      bins = CosineBins< 
        std::vector< double > >( njoy::utility::copy( newBins ) );

      CHECK( ranges::equal( newBins, bins ) );

      CHECK_THROWS_AS(
          bins = invalid,
          exceptions::InvalidCosine&
      );
    }
  }
} // SCENARIO
