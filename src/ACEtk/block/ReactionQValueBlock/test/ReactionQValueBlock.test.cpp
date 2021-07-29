#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/ReactionQValueBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ReactionQValueBlock = block::ReactionQValueBlock;

std::vector< double > chunk();
void verifyChunk( const ReactionQValueBlock& );

SCENARIO( "ReactionQValueBlock" ) {

  GIVEN( "valid data for a ReactionQValueBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > qvalues = { 2.22463100000E+00, 0., 0. };

      ReactionQValueBlock chunk( std::move( qvalues ) );

      THEN( "a ReactionQValueBlock can be constructed and members can "
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

      ReactionQValueBlock chunk( xss.begin(), xss.end(), 3 );

      THEN( "a ReactionQValueBlock can be constructed and members can "
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

  return { 2.22463100000E+00, 0., 0. };
}

void verifyChunk( const ReactionQValueBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 3 == chunk.length() );
  CHECK( "LQR" == chunk.name() );

  CHECK( 3 == chunk.NTR() );
  CHECK( 3 == chunk.numberReactions() );

  CHECK( 2.224631 == Approx( chunk.QValue(1) ) );
  CHECK( 0 == Approx( chunk.QValue(2) ) );
  CHECK( 0 == Approx( chunk.QValue(3) ) );

  CHECK( 3 == chunk.QValues().size() );
  CHECK( 2.224631 == Approx( chunk.QValues()[0] ) );
  CHECK( 0 == Approx( chunk.QValues()[1] ) );
  CHECK( 0 == Approx( chunk.QValues()[2] ) );
}
