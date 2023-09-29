#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/continuous/MultiplicityReactionNumberBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using MultiplicityReactionNumberBlock = block::MultiplicityReactionNumberBlock;

std::vector< double > chunk();
void verifyChunk( const MultiplicityReactionNumberBlock& );

SCENARIO( "MultiplicityReactionNumberBlock" ) {

  GIVEN( "valid data for a MultiplicityReactionNumberBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > reactions = { 102, 204, 444 };

      MultiplicityReactionNumberBlock chunk( std::move( reactions ) );

      THEN( "a MultiplicityReactionNumberBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      MultiplicityReactionNumberBlock chunk( xss.begin(), xss.end() );

      THEN( "a MultiplicityReactionNumberBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 3, 102, 204, 444 };
}

void verifyChunk( const MultiplicityReactionNumberBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 4 == chunk.length() );
  CHECK( "YP" == chunk.name() );

  CHECK( 3 == chunk.NYP() );
  CHECK( 3 == chunk.numberReactions() );

  CHECK( 102 == chunk.MT(1) );
  CHECK( 204 == chunk.MT(2) );
  CHECK( 444 == chunk.MT(3) );

  CHECK( 3 == chunk.MTs().size() );
  CHECK( 102 == chunk.MTs()[0] );
  CHECK( 204 == chunk.MTs()[1] );
  CHECK( 444 == chunk.MTs()[2] );

  CHECK( true == chunk.hasMT(102) );
  CHECK( true == chunk.hasMT(204) );
  CHECK( true == chunk.hasMT(444) );
  CHECK( false == chunk.hasMT(1) );

  CHECK( 1 == chunk.index(102) );
  CHECK( 2 == chunk.index(204) );
  CHECK( 3 == chunk.index(444) );

  CHECK_THROWS( chunk.index(1) );
}
