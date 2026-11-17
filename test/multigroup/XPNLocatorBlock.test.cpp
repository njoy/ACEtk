// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/XPNLocatorBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using XPNLocatorBlock = multigroup::XPNLocatorBlock;

std::vector< double > chunk();
void verifyChunk( const XPNLocatorBlock&, const std::vector< double >& );
XPNLocatorBlock makeDummyBlock();

SCENARIO( "XPNLocatorBlock" ) {

  GIVEN( "valid data for a XPNLocatorBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > locators = { 834, 0 };

      XPNLocatorBlock chunk( std::move( locators ) );

      THEN( "a XPNLocatorBlock can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      XPNLocatorBlock chunk( xss.begin(), xss.end(), 1 );

      THEN( "a XPNLocatorBlock can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      XPNLocatorBlock chunk( xss.begin(), xss.end(), 1 );
      XPNLocatorBlock copy( chunk );

      THEN( "an XPNLocatorBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      XPNLocatorBlock chunk( xss.begin(), xss.end(), 1 );
      XPNLocatorBlock move( std::move( chunk ) );

      THEN( "an XPNLocatorBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      XPNLocatorBlock chunk( xss.begin(), xss.end(), 1 );
      XPNLocatorBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an XPNLocatorBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      XPNLocatorBlock chunk( xss.begin(), xss.end(), 1 );
      XPNLocatorBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an XPNLocatorBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 834, 0 };
}

void verifyChunk( const XPNLocatorBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.length() );
  CHECK( "XPNL" == chunk.name() );

  CHECK( 1 == chunk.NSEC() );
  CHECK( 1 == chunk.numberSecondaryParticleTypes() );

  CHECK( 834 == chunk.LXPN1( ) );
  CHECK( 834 == chunk.incidentLocator( ) );

  CHECK( 0 == chunk.LXPN( 1 ) );
  CHECK( 0 == chunk.secondaryLocator( 1 ) );

  CHECK( true == chunk.isIsotropic( 1 ) );
  CHECK( false == chunk.incidentIsotropic( ) );
}

XPNLocatorBlock makeDummyBlock() {

  return { { { 834, 0 } } };
}
