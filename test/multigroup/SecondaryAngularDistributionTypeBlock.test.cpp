// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/SecondaryAngularDistributionTypeBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using SecondaryAngularDistributionTypeBlock = multigroup::SecondaryAngularDistributionTypeBlock;

std::vector< double > chunk();
void verifyChunk( const SecondaryAngularDistributionTypeBlock&, const std::vector< double >& );
SecondaryAngularDistributionTypeBlock makeDummyBlock();

SCENARIO( "SecondaryAngularDistributionTypeBlock" ) {

  GIVEN( "valid data for a SecondaryAngularDistributionTypeBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > types = { 0, 1, 0 };

      SecondaryAngularDistributionTypeBlock chunk( std::move( types ) );

      THEN( "a SecondaryAngularDistributionTypeBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      SecondaryAngularDistributionTypeBlock chunk( xss.begin(), xss.end(), 3 );

      THEN( "a SecondaryAngularDistributionTypeBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      SecondaryAngularDistributionTypeBlock chunk( xss.begin(), xss.end(), 3 );
      SecondaryAngularDistributionTypeBlock copy( chunk );

      THEN( "an SecondaryAngularDistributionTypeBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      SecondaryAngularDistributionTypeBlock chunk( xss.begin(), xss.end(), 3 );
      SecondaryAngularDistributionTypeBlock move( std::move( chunk ) );

      THEN( "an SecondaryAngularDistributionTypeBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      SecondaryAngularDistributionTypeBlock chunk( xss.begin(), xss.end(), 3 );
      SecondaryAngularDistributionTypeBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an SecondaryAngularDistributionTypeBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      SecondaryAngularDistributionTypeBlock chunk( xss.begin(), xss.end(), 3 );
      SecondaryAngularDistributionTypeBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an SecondaryAngularDistributionTypeBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 0, 1, 0 };
}

void verifyChunk( const SecondaryAngularDistributionTypeBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 3 == chunk.length() );
  CHECK( "SANG2" == chunk.name() );

  CHECK( 3 == chunk.NSEC() );
  CHECK( 3 == chunk.numberSecondaryParticles() );

  CHECK( 0  == chunk.SANG2( 1 ) );
  CHECK( 1  == chunk.SANG2( 2 ) );
  CHECK( 0  == chunk.SANG2( 3 ) );

  CHECK( 3 == chunk.SANG2s().size() );
  CHECK( 0  == chunk.SANG2s()[0] );

}

SecondaryAngularDistributionTypeBlock makeDummyBlock() {

  return { { 1 } };
}
