// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/PNLocatorBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PNLocatorBlock = multigroup::PNLocatorBlock;

std::vector< double > chunk();
void verifyChunk( const PNLocatorBlock&, const std::vector< double >& );
PNLocatorBlock makeDummyBlock();

SCENARIO( "PNLocatorBlock" ) {

  GIVEN( "valid data for a PNLocatorBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > locators = { 1299, 0 };

      PNLocatorBlock chunk( std::move( locators ) );

      THEN( "a PNLocatorBlock can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      PNLocatorBlock chunk( xss.begin(), xss.end(), 1 );

      THEN( "a PNLocatorBlock can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      PNLocatorBlock chunk( xss.begin(), xss.end(), 1 );
      PNLocatorBlock copy( chunk );

      THEN( "an PNLocatorBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      PNLocatorBlock chunk( xss.begin(), xss.end(), 1 );
      PNLocatorBlock move( std::move( chunk ) );

      THEN( "an PNLocatorBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      PNLocatorBlock chunk( xss.begin(), xss.end(), 1 );
      PNLocatorBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an PNLocatorBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      PNLocatorBlock chunk( xss.begin(), xss.end(), 1 );
      PNLocatorBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an PNLocatorBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 1299, 0 };
}

void verifyChunk( const PNLocatorBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.length() );
  CHECK( "PNL" == chunk.name() );

  CHECK( 1 == chunk.NSEC() );
  CHECK( 1 == chunk.numberSecondaryParticleTypes() );

  CHECK( 1299 == chunk.LPN1( ) );
  CHECK( 1299 == chunk.incidentLocator( ) );

  CHECK( 0 == chunk.LPN( 1 ) );
  CHECK( 0 == chunk.secondaryLocator( 1 ) );

  CHECK( true == chunk.isIsotropic( 1 ) );
  CHECK( false == chunk.incidentIsotropic( ) );
}

PNLocatorBlock makeDummyBlock() {

  return { { { 1299, 0 } } };
}
