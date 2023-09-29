#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/continuous/SecondaryParticleInformationBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using SecondaryParticleInformationBlock = block::SecondaryParticleInformationBlock;

std::vector< double > chunk();
void verifyChunk( const SecondaryParticleInformationBlock& );

SCENARIO( "SecondaryParticleInformationBlock" ) {

  GIVEN( "valid data for a SecondaryParticleInformationBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > numbers = { 3, 2, 4 };

      SecondaryParticleInformationBlock chunk( std::move( numbers ) );

      THEN( "a SecondaryParticleInformationBlock can be constructed and members "
            "bcan e tested" ) {

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

      SecondaryParticleInformationBlock chunk( xss.begin(), xss.end(), 3 );

      THEN( "a SecondaryParticleInformationBlock can be constructed and members "
            "can be tested" ) {

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

  return { 3, 2, 4 };
}

void verifyChunk( const SecondaryParticleInformationBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 3 == chunk.length() );
  CHECK( "NTRO" == chunk.name() );

  CHECK( 3 == chunk.NTYPE() );
  CHECK( 3 == chunk.numberAdditionalSecondaryParticleTypes() );

  CHECK( 3  == chunk.NP(1) );
  CHECK( 2 == chunk.NP(2) );
  CHECK( 4 == chunk.NP(3) );

  CHECK( 3 == chunk.NPs().size() );
  CHECK( 3  == chunk.NPs()[0] );
  CHECK( 2 == chunk.NPs()[1] );
  CHECK( 4 == chunk.NPs()[2] );
}
