// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/ReactionQValueBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ReactionQValueBlock = continuous::ReactionQValueBlock;

std::vector< double > chunk();
void verifyChunk( const ReactionQValueBlock&, const std::vector< double >& );
ReactionQValueBlock makeDummyBlock();

SCENARIO( "ReactionQValueBlock" ) {

  GIVEN( "valid data for a ReactionQValueBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > qvalues = { 2.22463100000E+00, 0., 0. };

      ReactionQValueBlock chunk( std::move( qvalues ) );

      THEN( "a ReactionQValueBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      ReactionQValueBlock chunk( xss.begin(), xss.end(), 3 );

      THEN( "a ReactionQValueBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 2.22463100000E+00, 0., 0. };
}

void verifyChunk( const ReactionQValueBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 3 == chunk.length() );
  CHECK( "LQR" == chunk.name() );

  CHECK( 3 == chunk.NTR() );
  CHECK( 3 == chunk.numberReactions() );

  CHECK_THAT( 2.224631, WithinRel( chunk.QValue(1) ) );
  CHECK_THAT( 0, WithinRel( chunk.QValue(2) ) );
  CHECK_THAT( 0, WithinRel( chunk.QValue(3) ) );

  CHECK( 3 == chunk.QValues().size() );
  CHECK_THAT( 2.224631, WithinRel( chunk.QValues()[0] ) );
  CHECK_THAT( 0, WithinRel( chunk.QValues()[1] ) );
  CHECK_THAT( 0, WithinRel( chunk.QValues()[2] ) );
}
