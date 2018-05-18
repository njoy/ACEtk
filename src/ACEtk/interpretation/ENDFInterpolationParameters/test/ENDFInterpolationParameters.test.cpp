#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Constructing coupled density functions" ){
  std::vector< double > NBT{ 1, 2, 3, 4, 5, 6 };
  GIVEN( "valid NBT and schemes" ){
    std::vector< std::vector< double > > validINT{
      {  1,  2,  3,  4,  5,  6 },
      { 11, 12, 13, 14, 15, 11 },
      { 21, 22, 23, 24, 25, 21 },
    };
    WHEN( "constructing ENDFInterpolationParameters" ){
      THEN( "the parameters can be checked" ){
        for( size_t i=0; i<validINT.size(); i++ ){
          auto INT = validINT[i];
          ENDFInterpolationParameters EIP(NBT, INT);
          REQUIRE( ranges::equal( NBT, EIP.NBT() ) );
          REQUIRE( ranges::equal( INT, EIP.schemes() ) );
        }
      }
    }
  } // GIVEN
  GIVEN( "inalid schemes" ){
    std::vector< std::vector< double > > invalidINT{
      {  1,  2,  3,  4,  5 },
      {  1,  2,  3,  4,  5,  0 },
      {  1,  2,  3,  4,  5,  7 },
      {  1,  2,  3,  4,  5,  8 },
      {  1,  2,  3,  4,  5,  9 },
      {  1,  2,  3,  4,  5, 10 },
      {  1,  2,  3,  4,  5, 16 },
      {  1,  2,  3,  4,  5, 17 },
      {  1,  2,  3,  4,  5, 18 },
      {  1,  2,  3,  4,  5, 19 },
      {  1,  2,  3,  4,  5, 20 },
    };
    WHEN( "trying to construct ENDFInterpolationParameters" ){
      THEN( "an exception is thrown" ){
        for( size_t i=0; i < invalidINT.size(); i++ ){
          auto INT = invalidINT[i];
          REQUIRE_THROWS( ENDFInterpolationParameters(NBT, INT) );
        }
      }
    }
  }
} // SCENARIO
