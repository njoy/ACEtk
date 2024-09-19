// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/DelayedNeutronPrecursorBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using DelayedNeutronPrecursorBlock = continuous::DelayedNeutronPrecursorBlock;
using DelayedNeutronPrecursorData = continuous::DelayedNeutronPrecursorData;

std::vector< double > chunk();
void verifyChunk( const DelayedNeutronPrecursorBlock&, const std::vector< double >& );
DelayedNeutronPrecursorBlock makeDummyBlock();

SCENARIO( "DelayedNeutronPrecursorBlock" ) {

  GIVEN( "valid data for a DelayedNeutronPrecursorBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< DelayedNeutronPrecursorData > groups = {

        DelayedNeutronPrecursorData( 1, 2.3e-4,
                                     { 1e-5, 1., 20. },
                                     { 1.2e-3, 2.5e-2, 1. } ),
        DelayedNeutronPrecursorData( 2, 3.2e-4,
                                     { 1e-5, 20. },
                                     { 2.4e-3, 2. } )
      };

      DelayedNeutronPrecursorBlock chunk( std::move( groups ) );

      THEN( "a DelayedNeutronPrecursorBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      DelayedNeutronPrecursorBlock chunk( xss.begin(), xss.end(), 2 );

      THEN( "a DelayedNeutronPrecursorBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {  2.30000000000E-04,                   0,                   3,
            1.00000000000E-05,   1.00000000000E+00,   2.00000000000E+01,   1.20000000000E-03,
            2.50000000000E-02,   1.00000000000E+00,
            3.20000000000E-04,                   0,                   2,
            1.00000000000E-05,   2.00000000000E+01,   2.40000000000E-03,   2.00000000000E+00 };
}

void verifyChunk( const DelayedNeutronPrecursorBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 16 == chunk.length() );
  CHECK( "BDD" == chunk.name() );

  CHECK( 2 == chunk.NPCR() );
  CHECK( 2 == chunk.numberDelayedPrecursors() );
  CHECK( 2 == chunk.data().size() );

  decltype(auto) group1 = chunk.precursorGroupData( 1 );
  CHECK( 1 == group1.number() );

  CHECK_THAT( 2.3e-4, WithinRel( group1.DEC() ) );
  CHECK_THAT( 2.3e-4, WithinRel( group1.decayConstant() ) );

  CHECK( 0 == group1.interpolationData().NB() );
  CHECK( 0 == group1.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == group1.interpolationData().INT().size() );
  CHECK( 0 == group1.interpolationData().interpolants().size() );
  CHECK( 0 == group1.interpolationData().NBT().size() );
  CHECK( 0 == group1.interpolationData().boundaries().size() );

  CHECK( 0 == group1.NB() );
  CHECK( 0 == group1.numberInterpolationRegions() );
  CHECK( 0 == group1.INT().size() );
  CHECK( 0 == group1.interpolants().size() );
  CHECK( 0 == group1.NBT().size() );
  CHECK( 0 == group1.boundaries().size() );

  CHECK( 3 == group1.NE() );
  CHECK( 3 == group1.numberValues() );

  CHECK( 3 == group1.energies().size() );
  CHECK_THAT( 1e-5, WithinRel( group1.energies()[0] ) );
  CHECK_THAT( 1., WithinRel( group1.energies()[1] ) );
  CHECK_THAT( 20., WithinRel( group1.energies()[2] ) );

  CHECK( 3 == group1.probabilities().size() );
  CHECK_THAT( 1.2e-3, WithinRel( group1.probabilities()[0] ) );
  CHECK_THAT( 2.5e-2, WithinRel( group1.probabilities()[1] ) );
  CHECK_THAT( 1., WithinRel( group1.probabilities()[2] ) );

  decltype(auto) group2 = chunk.precursorGroupData( 2 );
  CHECK( 2 == group2.number() );

  CHECK_THAT( 3.2e-4, WithinRel( group2.DEC() ) );
  CHECK_THAT( 3.2e-4, WithinRel( group2.decayConstant() ) );

  CHECK( 0 == group2.interpolationData().NB() );
  CHECK( 0 == group2.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == group2.interpolationData().INT().size() );
  CHECK( 0 == group2.interpolationData().interpolants().size() );
  CHECK( 0 == group2.interpolationData().NBT().size() );
  CHECK( 0 == group2.interpolationData().boundaries().size() );

  CHECK( 0 == group2.NB() );
  CHECK( 0 == group2.numberInterpolationRegions() );
  CHECK( 0 == group2.INT().size() );
  CHECK( 0 == group2.interpolants().size() );
  CHECK( 0 == group2.NBT().size() );
  CHECK( 0 == group2.boundaries().size() );

  CHECK( 2 == group2.NE() );
  CHECK( 2 == group2.numberValues() );

  CHECK( 2 == group2.energies().size() );
  CHECK_THAT( 1e-5, WithinRel( group2.energies()[0] ) );
  CHECK_THAT( 20., WithinRel( group2.energies()[1] ) );

  CHECK( 2 == group2.probabilities().size() );
  CHECK_THAT( 2.4e-3, WithinRel( group2.probabilities()[0] ) );
  CHECK_THAT( 2., WithinRel( group2.probabilities()[1] ) );
}
