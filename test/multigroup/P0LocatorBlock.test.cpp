// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/P0LocatorBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using P0LocatorBlock = multigroup::P0LocatorBlock;

std::vector< double > chunk();
void verifyChunk( const P0LocatorBlock&, const std::vector< double >& );
P0LocatorBlock makeDummyBlock();

SCENARIO( "P0LocatorBlock" ) {

  GIVEN( "valid data for a P0LocatorBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > locators = { 369, 2880 };

      P0LocatorBlock chunk( std::move( locators ) );

      THEN( "a P0LocatorBlock can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      P0LocatorBlock chunk( xss.begin(), xss.end(), 1 );

      THEN( "a P0LocatorBlock can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      P0LocatorBlock chunk( xss.begin(), xss.end(), 1 );
      P0LocatorBlock copy( chunk );

      THEN( "an P0LocatorBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      P0LocatorBlock chunk( xss.begin(), xss.end(), 1 );
      P0LocatorBlock move( std::move( chunk ) );

      THEN( "an P0LocatorBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      P0LocatorBlock chunk( xss.begin(), xss.end(), 1 );
      P0LocatorBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an P0LocatorBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      P0LocatorBlock chunk( xss.begin(), xss.end(), 1 );
      P0LocatorBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an P0LocatorBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {369, 2880};
}

void verifyChunk( const P0LocatorBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.length() );
  CHECK( "P0L" == chunk.name() );

  CHECK( 1 == chunk.NSEC() );
  CHECK( 1 == chunk.numberSecondaryParticleTypes() );

  CHECK( 369 == chunk.P01( ) );
  CHECK( 369 == chunk.incidentLocator( ) );

  CHECK( 2880 == chunk.P02( 1 ) );
  CHECK( 2880 == chunk.secondaryLocator( 1 ) );
}

P0LocatorBlock makeDummyBlock() {

  return { { { 369, 2880 } } };
}
