// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/SecondaryParticleTypeBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using SecondaryParticleTypeBlock = multigroup::SecondaryParticleTypeBlock;

std::vector< double > chunk();
void verifyChunk( const SecondaryParticleTypeBlock&, const std::vector< double >& );
SecondaryParticleTypeBlock makeDummyBlock();

SCENARIO( "SecondaryParticleTypeBlock" ) {

  GIVEN( "valid data for a SecondaryParticleTypeBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > types = { 1, 2 };

      SecondaryParticleTypeBlock chunk( std::move( types ) );

      THEN( "a SecondaryParticleTypeBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      SecondaryParticleTypeBlock chunk( xss.begin(), xss.end(), 2 );

      THEN( "a SecondaryParticleTypeBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      SecondaryParticleTypeBlock chunk( xss.begin(), xss.end(), 2 );
      SecondaryParticleTypeBlock copy( chunk );

      THEN( "an SecondaryParticleTypeBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      SecondaryParticleTypeBlock chunk( xss.begin(), xss.end(), 2 );
      SecondaryParticleTypeBlock move( std::move( chunk ) );

      THEN( "an SecondaryParticleTypeBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      SecondaryParticleTypeBlock chunk( xss.begin(), xss.end(), 2 );
      SecondaryParticleTypeBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an SecondaryParticleTypeBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      SecondaryParticleTypeBlock chunk( xss.begin(), xss.end(), 2 );
      SecondaryParticleTypeBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an SecondaryParticleTypeBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 1, 2 };
}

void verifyChunk( const SecondaryParticleTypeBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.length() );
  CHECK( "IPT" == chunk.name() );

  CHECK( 2 == chunk.NTYPE() );
  CHECK( 2 == chunk.numberSecondaryParticleTypes() );

  CHECK( 1  == chunk.IPT(1) );
  CHECK( 2  == chunk.IPT(2) );

  CHECK( 2 == chunk.IPTs().size() );
  CHECK( 1  == chunk.IPTs()[0] );

  CHECK( true == chunk.hasIPT(1) );
  CHECK( true == chunk.hasIPT(2) );
  CHECK( false == chunk.hasIPT(34) );

  CHECK( 1 == chunk.index(1) );
  CHECK( 2 == chunk.index(2) );

  // CHECK_THROWS( chunk.index(9) );
}

SecondaryParticleTypeBlock makeDummyBlock() {

  return { { 1 } };
}
