#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "creating ranges from interpolation parameters" ){
  GIVEN( "valid interpolation parameters" ){
    std::vector< double > NBT{ 3, 5 };
    std::vector< double > INT{ 3, 1 };

    ENDFInterpolationParameters EIP( NBT, INT );

    WHEN( "a range is created" ){
      auto interpolationRange = EIP.range();

      THEN( "the values can be verified" ){
        REQUIRE( 2 == interpolationRange.size() );

        REQUIRE( 3 == interpolationRange[ 0 ].first );
        REQUIRE( 0 == interpolationRange[ 0 ].second.first );
        REQUIRE( 3 == interpolationRange[ 0 ].second.second );

        REQUIRE( 1 == interpolationRange[ 1 ].first );
        REQUIRE( 3 == interpolationRange[ 1 ].second.first );
        REQUIRE( 5 == interpolationRange[ 1 ].second.second );
      }
    }
  }
} // SCENARIO
