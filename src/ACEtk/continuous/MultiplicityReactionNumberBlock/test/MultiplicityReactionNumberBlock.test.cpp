// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/MultiplicityReactionNumberBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using MultiplicityReactionNumberBlock = continuous::MultiplicityReactionNumberBlock;

std::vector< double > chunk();
void verifyChunk( const MultiplicityReactionNumberBlock&, const std::vector< double >& );
MultiplicityReactionNumberBlock makeDummyBlock();

SCENARIO( "MultiplicityReactionNumberBlock" ) {

  GIVEN( "valid data for a MultiplicityReactionNumberBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > reactions = { 102, 204, 444 };

      MultiplicityReactionNumberBlock chunk( std::move( reactions ) );

      THEN( "a MultiplicityReactionNumberBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      MultiplicityReactionNumberBlock chunk( xss.begin(), xss.end() );

      THEN( "a MultiplicityReactionNumberBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 3, 102, 204, 444 };
}

void verifyChunk( const MultiplicityReactionNumberBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

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
