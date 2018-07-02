#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details;

SCENARIO( "Verifying ENDFInterpolationParameters" ){
  GIVEN( "valid interpolation parameters" ){
    std::vector< double > validINT{
       1,  2,  3,  4,  5,  6, 11, 12, 13, 14, 15, 11, 21, 22, 23, 24, 25, 21
    };
    WHEN( "constructing ENDFInterpolationParameters" ){
      THEN( "the parameters can be checked" ){
        for( int INT : validINT ){
          // REQUIRE( verify::parameters( INT ) );
        }
      }
    }
  } // GIVEN
  GIVEN( "inalid interpolation parameters" ){
    std::vector< int > invalidINT{ 0, 7, 8, 9, 10, 16, 17, 18, 19, 20, };
      THEN( "the parameters can be checked" ){
        for( int INT : invalidINT ){
          // REQUIRE( not verify::parameters( INT ) );
        }
      }
  } // GIVEN invalid
} // SCENARIO
