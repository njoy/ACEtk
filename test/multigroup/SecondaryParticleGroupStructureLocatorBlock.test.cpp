// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/SecondaryParticleGroupStructureLocatorBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using SecondaryParticleGroupStructureLocatorBlock = multigroup::SecondaryParticleGroupStructureLocatorBlock;

std::vector< double > chunk();
void verifyChunk( const SecondaryParticleGroupStructureLocatorBlock&, const std::vector< double >& );
SecondaryParticleGroupStructureLocatorBlock makeDummyBlock();

SCENARIO( "SecondaryParticleGroupStructureLocatorBlock" ) {

  GIVEN( "valid data for a SecondaryParticleGroupStructureLocatorBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > locators = { 369, 2880 };

      SecondaryParticleGroupStructureLocatorBlock chunk( std::move( locators ) );

      THEN( "a SecondaryParticleGroupStructureLocatorBlock can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      SecondaryParticleGroupStructureLocatorBlock chunk( xss.begin(), xss.end(), 2 );

      THEN( "a SecondaryParticleGroupStructureLocatorBlock can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      SecondaryParticleGroupStructureLocatorBlock chunk( xss.begin(), xss.end(), 2 );
      SecondaryParticleGroupStructureLocatorBlock copy( chunk );

      THEN( "an SecondaryParticleGroupStructureLocatorBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      SecondaryParticleGroupStructureLocatorBlock chunk( xss.begin(), xss.end(), 2 );
      SecondaryParticleGroupStructureLocatorBlock move( std::move( chunk ) );

      THEN( "an SecondaryParticleGroupStructureLocatorBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      SecondaryParticleGroupStructureLocatorBlock chunk( xss.begin(), xss.end(), 2 );
      SecondaryParticleGroupStructureLocatorBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an SecondaryParticleGroupStructureLocatorBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      SecondaryParticleGroupStructureLocatorBlock chunk( xss.begin(), xss.end(), 2 );
      SecondaryParticleGroupStructureLocatorBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an SecondaryParticleGroupStructureLocatorBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {369, 2880};
}

void verifyChunk( const SecondaryParticleGroupStructureLocatorBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.length() );
  CHECK( "ERG2L" == chunk.name() );

  CHECK( 2 == chunk.NSEC() );
  CHECK( 2 == chunk.numberSecondaryParticleTypes() );

  CHECK( 369 == chunk.ERG2( 1 ) );
  CHECK( 2880 == chunk.ERG2( 2 ) );

  CHECK( 369 == chunk.locator( 1 ) );
  CHECK( 2880 == chunk.locator( 2 ) );
}

SecondaryParticleGroupStructureLocatorBlock makeDummyBlock() {

  return { { { 369, 2880 } } };
}
