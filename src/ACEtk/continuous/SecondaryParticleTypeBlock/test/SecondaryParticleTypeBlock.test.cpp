// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/SecondaryParticleTypeBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using SecondaryParticleTypeBlock = continuous::SecondaryParticleTypeBlock;

std::vector< double > chunk();
void verifyChunk( const SecondaryParticleTypeBlock& );

SCENARIO( "SecondaryParticleTypeBlock" ) {

  GIVEN( "valid data for a SecondaryParticleTypeBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > types = { 9, 31, 34 };

      SecondaryParticleTypeBlock chunk( std::move( types ) );

      THEN( "a SecondaryParticleTypeBlock can be constructed and members can "
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

      SecondaryParticleTypeBlock chunk( xss.begin(), xss.end(), 3 );

      THEN( "a SecondaryParticleTypeBlock can be constructed and members can "
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
} // SCENARIO

std::vector< double > chunk() {

  return { 9, 31, 34 };
}

void verifyChunk( const SecondaryParticleTypeBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 3 == chunk.length() );
  CHECK( "PTYPE" == chunk.name() );

  CHECK( 3 == chunk.NTYPE() );
  CHECK( 3 == chunk.numberAdditionalSecondaryParticleTypes() );

  CHECK( 9  == chunk.IP(1) );
  CHECK( 31 == chunk.IP(2) );
  CHECK( 34 == chunk.IP(3) );

  CHECK( 3 == chunk.IPs().size() );
  CHECK( 9  == chunk.IPs()[0] );
  CHECK( 31 == chunk.IPs()[1] );
  CHECK( 34 == chunk.IPs()[2] );

  CHECK( true == chunk.hasIP(9) );
  CHECK( true == chunk.hasIP(31) );
  CHECK( true == chunk.hasIP(34) );
  CHECK( false == chunk.hasIP(1) );

  CHECK( 1 == chunk.index(9) );
  CHECK( 2 == chunk.index(31) );
  CHECK( 3 == chunk.index(34) );

  CHECK_THROWS( chunk.index(1) );
}
