// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/EnergyDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using FrameAndMultiplicityBlock = continuous::FrameAndMultiplicityBlock;

std::vector< double > chunk();
std::vector< double > chunkTYRH();
void verifyChunk( const FrameAndMultiplicityBlock& );
void verifyChunkTYRH( const FrameAndMultiplicityBlock& );

SCENARIO( "FrameAndMultiplicityBlock" ) {

  GIVEN( "valid data for a FrameAndMultiplicityBlock instance as a TYR block" ) {

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

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
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

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a FrameAndMultiplicityBlock instance as a TYRH block" ) {

    std::vector< double > xss = chunkTYRH();

    WHEN( "the data is given explicitly" ) {

      std::vector< ReferenceFrame > frames = {

        ReferenceFrame::CentreOfMass,
        ReferenceFrame::Laboratory,
        ReferenceFrame::Laboratory
      };

      FrameAndMultiplicityBlock chunk( std::move( frames ) );

      THEN( "a FrameAndMultiplicityBlock can be constructed and members can "
            "be tested" ) {

        verifyChunkTYRH( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      FrameAndMultiplicityBlock chunk( xss.begin(), xss.end(), 3 );

      THEN( "a FrameAndMultiplicityBlock can be constructed and members can "
            "be tested" ) {

        verifyChunkTYRH( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { -2, 0, 0 };
}

std::vector< double > chunkTYRH() {

  return { -1, 1, 1 };
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

void verifyChunkTYRH( const FrameAndMultiplicityBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 3 == chunk.length() );
  CHECK( "TYR" == chunk.name() );

  CHECK( 3 == chunk.NTR() );
  CHECK( 3 == chunk.numberReactions() );

  CHECK( ReferenceFrame::CentreOfMass == chunk.referenceFrame(1) );
  CHECK( ReferenceFrame::Laboratory == chunk.referenceFrame(2) );
  CHECK( ReferenceFrame::Laboratory == chunk.referenceFrame(3) );

  CHECK( 1 == chunk.multiplicity(1) );
  CHECK( 1 == chunk.multiplicity(2) );
  CHECK( 1 == chunk.multiplicity(3) );

  CHECK( 3 == chunk.referenceFrames().size() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.referenceFrames()[0] );
  CHECK( ReferenceFrame::Laboratory == chunk.referenceFrames()[1] );
  CHECK( ReferenceFrame::Laboratory == chunk.referenceFrames()[2] );

  CHECK( 3 == chunk.multiplicities().size() );
  CHECK( 1 == chunk.multiplicities()[0] );
  CHECK( 1 == chunk.multiplicities()[1] );
  CHECK( 1 == chunk.multiplicities()[2] );
}
