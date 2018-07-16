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
          CHECK( verify::interpolationParameter( INT ) );
        }
        CHECK( verify::interpolationParameters( validINT ) );
      }
    }
    WHEN( "interpulation parameters are empty" ){
      std::vector< double > validINT;

      CHECK( verify::interpolationParameters( validINT ) );
    }
  } // GIVEN
  GIVEN( "invalid interpolation parameters" ){
    std::vector< int > invalidINT{ 0, 7, 8, 9, 10, 16, 17, 18, 19, 20 };
      THEN( "the parameters can be checked" ){
        for( int INT : invalidINT ){
          CHECK( not verify::interpolationParameter( INT ) );
        }
        CHECK( not verify::interpolationParameters( invalidINT ) );
      }
  } // GIVEN invalid
} // SCENARIO
