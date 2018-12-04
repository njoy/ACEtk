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
          CHECK_NOTHROW( verify::interpolationParameter( INT ) );
        }
        CHECK_NOTHROW( verify::interpolationParameters( validINT ) );
      }
    }
    WHEN( "interpulation parameters are empty" ){
      std::vector< double > validINT;

      CHECK_NOTHROW( verify::interpolationParameters( validINT ) );
    }
  } // GIVEN
  GIVEN( "invalid interpolation parameters" ){
    std::vector< int > invalidINT{ 0, 7, 8, 9, 10, 16, 17, 18, 19, 20 };
      THEN( "the parameters can be checked" ){
        for( int INT : invalidINT ){
          CHECK_THROWS_AS( 
            verify::interpolationParameter( INT ),
            verify::exceptions::InvalidENDFInterpolationParameter&
          );
        }
        CHECK_THROWS_AS( 
          verify::interpolationParameters( invalidINT ),
          verify::exceptions::InvalidENDFInterpolationParameter&
        );
      }
  } // GIVEN invalid
} // SCENARIO
