// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/SecondaryParticleLocatorBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using SecondaryParticleLocatorBlock = continuous::SecondaryParticleLocatorBlock;

std::vector< double > chunk();
void verifyChunk( const SecondaryParticleLocatorBlock&, const std::vector< double >& );
SecondaryParticleLocatorBlock makeDummyBlock();

SCENARIO( "SecondaryParticleLocatorBlock" ) {

  GIVEN( "valid data for a SecondaryParticleLocatorBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< std::array< unsigned int, 10 > > locators = {

        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
        { 101, 102, 103, 104, 105, 106, 107, 108, 109, 110 }
      };

      SecondaryParticleLocatorBlock chunk( std::move( locators ) );

      THEN( "a SecondaryParticleLocatorBlock can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      SecondaryParticleLocatorBlock chunk( xss.begin(), xss.end(), 2 );

      THEN( "a SecondaryParticleLocatorBlock can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
           101, 102, 103, 104, 105, 106, 107, 108, 109, 110 };
}

void verifyChunk( const SecondaryParticleLocatorBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 20 == chunk.length() );
  CHECK( "IXS" == chunk.name() );

  CHECK( 2 == chunk.NTYPE() );
  CHECK( 2 == chunk.numberAdditionalSecondaryParticleTypes() );

  CHECK( 1 == chunk.LLOC( 1, 1 ) );
  CHECK( 2 == chunk.LLOC( 1, 2 ) );
  CHECK( 3 == chunk.LLOC( 1, 3 ) );
  CHECK( 4 == chunk.LLOC( 1, 4 ) );
  CHECK( 5 == chunk.LLOC( 1, 5 ) );
  CHECK( 6 == chunk.LLOC( 1, 6 ) );
  CHECK( 7 == chunk.LLOC( 1, 7 ) );
  CHECK( 8 == chunk.LLOC( 1, 8 ) );
  CHECK( 9 == chunk.LLOC( 1, 9 ) );
  CHECK( 10 == chunk.LLOC( 1, 10 ) );
  CHECK( 101 == chunk.LLOC( 2, 1 ) );
  CHECK( 102 == chunk.LLOC( 2, 2 ) );
  CHECK( 103 == chunk.LLOC( 2, 3 ) );
  CHECK( 104 == chunk.LLOC( 2, 4 ) );
  CHECK( 105 == chunk.LLOC( 2, 5 ) );
  CHECK( 106 == chunk.LLOC( 2, 6 ) );
  CHECK( 107 == chunk.LLOC( 2, 7 ) );
  CHECK( 108 == chunk.LLOC( 2, 8 ) );
  CHECK( 109 == chunk.LLOC( 2, 9 ) );
  CHECK( 110 == chunk.LLOC( 2, 10 ) );

  CHECK( 1 == chunk.HPD( 1 ) );
  CHECK( 2 == chunk.MTRH( 1 ) );
  CHECK( 3 == chunk.TYRH( 1 ) );
  CHECK( 4 == chunk.LSIGH( 1 ) );
  CHECK( 5 == chunk.SIGH( 1 ) );
  CHECK( 6 == chunk.LANDH( 1 ) );
  CHECK( 7 == chunk.ANDH( 1 ) );
  CHECK( 8 == chunk.LDLWH( 1 ) );
  CHECK( 9 == chunk.DLWH( 1 ) );
  CHECK( 10 == chunk.YP( 1 ) );
  CHECK( 101 == chunk.HPD( 2 ) );
  CHECK( 102 == chunk.MTRH( 2 ) );
  CHECK( 103 == chunk.TYRH( 2 ) );
  CHECK( 104 == chunk.LSIGH( 2 ) );
  CHECK( 105 == chunk.SIGH( 2 ) );
  CHECK( 106 == chunk.LANDH( 2 ) );
  CHECK( 107 == chunk.ANDH( 2 ) );
  CHECK( 108 == chunk.LDLWH( 2 ) );
  CHECK( 109 == chunk.DLWH( 2 ) );
  CHECK( 110 == chunk.YP( 2 ) );
}
