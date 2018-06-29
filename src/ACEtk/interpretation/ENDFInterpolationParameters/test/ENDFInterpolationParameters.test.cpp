#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Constructing ENDFInterpolationParameters" ){
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
          REQUIRE( 6 == EIP.size() );

          REQUIRE( 0 == EIP.range()[ 0 ].indices().begin() );
          for( size_t j=0; j< INT.size(); j++ ){
            REQUIRE( NBT[ j ] == EIP.range()[ j+1 ].indices().begin() +1 );
            REQUIRE( NBT[ j ] == EIP.range()[ j ].indices().end() );
            REQUIRE( INT[ j ] == EIP.range()[ j ].scheme() );
            REQUIRE( NBT[ j ] == EIP.range().at( j ).indices().end() );
            REQUIRE( INT[ j ] == EIP.range().at( j ).scheme() );
          }
        }
      }
    }
    WHEN( "NBT and INT are empty" ){
      std::vector< double > NBT;
      std::vector< double > INT;

      ENDFInterpolationParameters EIP( NBT, INT );

      THEN( "the size is zero" ){
        REQUIRE( 0 == EIP.size() );
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
  GIVEN( "invalid index" ){
    std::vector< double > NBT{ 1, 2, 3 };
    std::vector< double > INT{ 1,  2,  3 };

    ENDFInterpolationParameters EIP{ NBT, INT };

    THEN( "an exception is thrown" ){
      int index = 4;
      REQUIRE_THROWS( EIP.range().at( index ) );
    }
  }
} // SCENARIO
