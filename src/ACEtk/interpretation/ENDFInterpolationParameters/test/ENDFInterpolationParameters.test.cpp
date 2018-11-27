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
        for( auto INT : validINT ){
          ENDFInterpolationParameters EIP(NBT, INT);
          CHECK( ranges::equal( NBT, EIP.NBT() ) );
          CHECK( ranges::equal( INT, EIP.schemes() ) );
          CHECK( 6 == EIP.size() );

          CHECK( 0 == EIP.range()[ 0 ].indices().begin() );
          
          ranges::view::zip_with( [](auto nbt, auto eip){ 
                   CHECK( nbt == eip.indices().begin() + 1 ); }, 
                    NBT, EIP.range() | ranges::view::drop_exactly( 1 ) );

          for( size_t j=0; j< INT.size(); j++ ){
            CHECK( NBT[ j ] == EIP.range()[ j ].indices().end() );
            CHECK( INT[ j ] == EIP.range()[ j ].scheme() );
            CHECK( NBT[ j ] == EIP.range().at( j ).indices().end() );
            CHECK( INT[ j ] == EIP.range().at( j ).scheme() );
          }
        }
      }
    }
    WHEN( "NBT and INT are empty" ){
      std::vector< double > NBT;
      std::vector< double > INT;

      ENDFInterpolationParameters EIP( NBT, INT );

      THEN( "the size is zero" ){
        CHECK( 0 == EIP.size() );
      }
    }
  } // GIVEN
  GIVEN( "invalid schemes" ){
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
          CHECK_THROWS( ENDFInterpolationParameters(NBT, INT) );
        }
      }
    }
  }
  GIVEN( "invalid NBT" ){
    std::vector< double > INT{ 1, 2, 3, 4, 5, 6 };
    WHEN( "NBT is negative" ){
      std::vector< double > NBT{ -1, 2, 3, 4, 5, 6 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS( ENDFInterpolationParameters( NBT, INT ) );
      }
    }
    WHEN( "NBT is not sorted" ){
      std::vector< double > NBT{ 1, 2, 3, 4, 5, 3 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS( ENDFInterpolationParameters( NBT, INT ) );
      }
    }
  }

  GIVEN( "invalid index" ){
    std::vector< double > NBT{ 1, 2, 3 };
    std::vector< double > INT{ 1,  2,  3 };

    ENDFInterpolationParameters EIP{ NBT, INT };

    THEN( "an exception is thrown" ){
      int index = 4;
      CHECK_THROWS( EIP.range().at( index ) );
    }
  }
} // SCENARIO
