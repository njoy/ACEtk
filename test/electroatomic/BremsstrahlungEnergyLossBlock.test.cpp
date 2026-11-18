// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electroatomic/BremsstrahlungEnergyLossBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using BremsstrahlungEnergyLossBlock = electroatomic::BremsstrahlungEnergyLossBlock;

std::vector< double > chunk();
void verifyChunk( const BremsstrahlungEnergyLossBlock&, const std::vector< double >& );
BremsstrahlungEnergyLossBlock makeDummyBlock();

SCENARIO( "BremsstrahlungEnergyLossBlock" ) {

  GIVEN( "valid data for a BremsstrahlungEnergyLossBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 10., 20., 200. };
      std::vector< double > loss = { 1., 2., 3. };

      BremsstrahlungEnergyLossBlock chunk( std::move( energies ), std::move( loss ) );

      THEN( "a BremsstrahlungEnergyLossBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      BremsstrahlungEnergyLossBlock chunk( xss.begin(), xss.end(), 3 );

      THEN( "a BremsstrahlungEnergyLossBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      BremsstrahlungEnergyLossBlock chunk( xss.begin(), xss.end(), 3 );
      BremsstrahlungEnergyLossBlock copy( chunk );

      THEN( "a BremsstrahlungEnergyLossBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      BremsstrahlungEnergyLossBlock chunk( xss.begin(), xss.end(), 3 );
      BremsstrahlungEnergyLossBlock move( std::move( chunk ) );

      THEN( "a BremsstrahlungEnergyLossBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      BremsstrahlungEnergyLossBlock chunk( xss.begin(), xss.end(), 3 );
      BremsstrahlungEnergyLossBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "a BremsstrahlungEnergyLossBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      BremsstrahlungEnergyLossBlock chunk( xss.begin(), xss.end(), 3 );
      BremsstrahlungEnergyLossBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "a BremsstrahlungEnergyLossBlock can be move assigned and "
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

void verifyChunk( const BremsstrahlungEnergyLossBlock& chunk,
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
  CHECK( 3 == chunk.energyLoss().size() );

  CHECK_THAT(  10., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT(  20., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 200., WithinRel( chunk.energies()[2] ) );

  CHECK_THAT(   1., WithinRel( chunk.energyLoss()[0] ) );
  CHECK_THAT(   2., WithinRel( chunk.energyLoss()[1] ) );
  CHECK_THAT(   3., WithinRel( chunk.energyLoss()[2] ) );
}

BremsstrahlungEnergyLossBlock makeDummyBlock() {

  return { { 1., 2. }, { 3., 4. } };
}
