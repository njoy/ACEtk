// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/ElasticCrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ElasticCrossSectionBlock = electron::ElasticCrossSectionBlock;

std::vector< double > chunk();
void verifyChunk( const ElasticCrossSectionBlock&, const std::vector< double >& );
ElasticCrossSectionBlock makeDummyBlock();

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

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      ElasticCrossSectionBlock chunk( xss.begin(), xss.end(), 3 );

      THEN( "a ElasticCrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  // first value of the second xs increased by 1 for testing purposes
  return {   1.,   2.,   3.,
             4.,   5.,   6. };
}

void verifyChunk( const ElasticCrossSectionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 6 == chunk.length() );
  CHECK( "SELAS" == chunk.name() );

  CHECK( 3 == chunk.NE() );
  CHECK( 3 == chunk.numberEnergyPoints() );

  CHECK( 3 == chunk.transport().size() );
  CHECK( 3 == chunk.total().size() );

  CHECK_THAT(   1., WithinRel( chunk.transport()[0] ) );
  CHECK_THAT(   2., WithinRel( chunk.transport()[1] ) );
  CHECK_THAT(   3., WithinRel( chunk.transport()[2] ) );
  CHECK_THAT(   4., WithinRel( chunk.total()[0] ) );
  CHECK_THAT(   5., WithinRel( chunk.total()[1] ) );
  CHECK_THAT(   6., WithinRel( chunk.total()[2] ) );
}
