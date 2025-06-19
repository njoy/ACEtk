// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/BremsstrahlungBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using BremsstrahlungBlock = electron::BremsstrahlungBlock;

std::vector< double > chunk();
void verifyChunk( const BremsstrahlungBlock&, const std::vector< double >& );
BremsstrahlungBlock makeDummyBlock();

SCENARIO( "BremsstrahlungBlock" ) {

  GIVEN( "valid data for a BremsstrahlungBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 10., 20., 200. };
      std::vector< double > remaining = { 1., 2., 3. };

      BremsstrahlungBlock chunk( std::move( energies ), std::move( remaining ) );

      THEN( "a PhotoatomicElectronShellBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      BremsstrahlungBlock chunk( xss.begin(), xss.end(), 3 );

      THEN( "a PhotoatomicElectronShellBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      BremsstrahlungBlock chunk( xss.begin(), xss.end(), 3 );
      BremsstrahlungBlock copy( chunk );

      THEN( "an BremsstrahlungBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      BremsstrahlungBlock chunk( xss.begin(), xss.end(), 3 );
      BremsstrahlungBlock move( std::move( chunk ) );

      THEN( "an BremsstrahlungBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      BremsstrahlungBlock chunk( xss.begin(), xss.end(), 3 );
      BremsstrahlungBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an BremsstrahlungBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      BremsstrahlungBlock chunk( xss.begin(), xss.end(), 3 );
      BremsstrahlungBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an BremsstrahlungBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {  10.,  20., 200.,
             1.,   2.,   3. };
}

void verifyChunk( const BremsstrahlungBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 6 == chunk.length() );
  CHECK( "BREML" == chunk.name() );

  CHECK( 3 == chunk.NBL() );
  CHECK( 3 == chunk.numberEnergyPoints() );

  CHECK( 3 == chunk.energies().size() );
  CHECK( 3 == chunk.energyAfterBremsstrahlung().size() );

  CHECK_THAT(  10., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT(  20., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 200., WithinRel( chunk.energies()[2] ) );

  CHECK_THAT(   1., WithinRel( chunk.energyAfterBremsstrahlung()[0] ) );
  CHECK_THAT(   2., WithinRel( chunk.energyAfterBremsstrahlung()[1] ) );
  CHECK_THAT(   3., WithinRel( chunk.energyAfterBremsstrahlung()[2] ) );
}

BremsstrahlungBlock makeDummyBlock() {

  return { { 1., 2. }, { 3., 4. } };
}
