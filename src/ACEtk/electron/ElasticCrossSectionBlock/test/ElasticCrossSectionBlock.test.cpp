#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/electron/ElasticCrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ElasticCrossSectionBlock = electron::ElasticCrossSectionBlock;

std::vector< double > chunk();
void verifyChunk( const ElasticCrossSectionBlock& );

SCENARIO( "ElasticCrossSectionBlock" ) {

  GIVEN( "valid data for a ElasticCrossSectionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > transport = { 1., 2., 3. };
      std::vector< double > total = { 4., 5., 6. };

      ElasticCrossSectionBlock
      chunk( std::move( transport ), std::move( total ) );

      THEN( "a ElasticCrossSectionBlock can be constructed and "
            "members can be tested" ) {

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

      ElasticCrossSectionBlock chunk( xss.begin(), xss.end(), 3 );

      THEN( "a ElasticCrossSectionBlock can be constructed and "
            "members can be tested" ) {

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

  // first value of the second xs increased by 1 for testing purposes
  return {   1.,   2.,   3.,
             4.,   5.,   6. };
}

void verifyChunk( const ElasticCrossSectionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 6 == chunk.length() );
  CHECK( "SELAS" == chunk.name() );

  CHECK( 3 == chunk.NE() );
  CHECK( 3 == chunk.numberEnergyPoints() );

  CHECK( 3 == chunk.transport().size() );
  CHECK( 3 == chunk.total().size() );

  CHECK(   1. == Approx( chunk.transport()[0] ) );
  CHECK(   2. == Approx( chunk.transport()[1] ) );
  CHECK(   3. == Approx( chunk.transport()[2] ) );
  CHECK(   4. == Approx( chunk.total()[0] ) );
  CHECK(   5. == Approx( chunk.total()[1] ) );
  CHECK(   6. == Approx( chunk.total()[2] ) );
}
