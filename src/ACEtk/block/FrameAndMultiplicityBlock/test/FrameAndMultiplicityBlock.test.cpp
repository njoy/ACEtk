#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/FrameAndMultiplicityBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using FrameAndMultiplicityBlock = block::FrameAndMultiplicityBlock;

std::vector< double > chunk();
void verifyChunk( const FrameAndMultiplicityBlock& );

SCENARIO( "FrameAndMultiplicityBlock" ) {

  GIVEN( "valid data for a FrameAndMultiplicityBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< ReferenceFrame > frames = {

        ReferenceFrame::CentreOfMass,
        ReferenceFrame::Laboratory,
        ReferenceFrame::Laboratory
      };
      std::vector< unsigned int > multiplicities = { 2, 0, 0 };

      FrameAndMultiplicityBlock chunk( std::move( frames ),
                                       std::move( multiplicities ) );

      THEN( "a FrameAndMultiplicityBlock can be constructed and members can "
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

      FrameAndMultiplicityBlock chunk( xss.begin(), xss.end(), 3 );

      THEN( "a FrameAndMultiplicityBlock can be constructed and members can "
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

  return { -2, 0, 0 };
}

void verifyChunk( const FrameAndMultiplicityBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 3 == chunk.length() );
  CHECK( "TYR" == chunk.name() );

  CHECK( 3 == chunk.NTR() );
  CHECK( 3 == chunk.numberReactions() );

  CHECK( ReferenceFrame::CentreOfMass == chunk.referenceFrame(1) );
  CHECK( ReferenceFrame::Laboratory == chunk.referenceFrame(2) );
  CHECK( ReferenceFrame::Laboratory == chunk.referenceFrame(3) );

  CHECK( 2 == chunk.multiplicity(1) );
  CHECK( 0 == chunk.multiplicity(2) );
  CHECK( 0 == chunk.multiplicity(3) );

  CHECK( 3 == chunk.referenceFrames().size() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.referenceFrames()[0] );
  CHECK( ReferenceFrame::Laboratory == chunk.referenceFrames()[1] );
  CHECK( ReferenceFrame::Laboratory == chunk.referenceFrames()[2] );

  CHECK( 3 == chunk.multiplicities().size() );
  CHECK( 2 == chunk.multiplicities()[0] );
  CHECK( 0 == chunk.multiplicities()[1] );
  CHECK( 0 == chunk.multiplicities()[2] );
}
