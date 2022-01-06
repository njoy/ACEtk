#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/DelayedNeutronPrecursorBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using DelayedNeutronPrecursorBlock = block::DelayedNeutronPrecursorBlock;
using DelayedNeutronPrecursorData = block::DelayedNeutronPrecursorData;

std::vector< double > chunk();
void verifyChunk( const DelayedNeutronPrecursorBlock& );

SCENARIO( "DelayedNeutronPrecursorBlock" ) {

  GIVEN( "valid data for a DelayedNeutronPrecursorBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< DelayedNeutronPrecursorData > groups = {

        DelayedNeutronPrecursorData( 2.3e-4,
                                     { 1e-5, 1., 20. },
                                     { 1.2e-3, 2.5e-2, 1. } ),
        DelayedNeutronPrecursorData( 3.2e-4,
                                     { 1e-5, 20. },
                                     { 2.4e-3, 2. } ),
      };

      DelayedNeutronPrecursorBlock chunk( std::move( groups ) );

      THEN( "a DelayedNeutronPrecursorBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      DelayedNeutronPrecursorBlock chunk( xss.begin(), xss.end(), 2);

      THEN( "a DelayedNeutronPrecursorBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {  2.30000000000E-04,                   0,                   3,
            1.00000000000E-11,   1.00000000000E+00,   2.00000000000E+01,   1.20000000000E-03,
            2.50000000000E-02,   1.00000000000E+00,
            3.20000000000E-04,                   0,                   2,
            1.00000000000E-11,   2.00000000000E+01,   2.40000000000E-03,   2.00000000000E+00 };
}

void verifyChunk( const DelayedNeutronPrecursorBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 16 == chunk.length() );
  CHECK( "BDD" == chunk.name() );

  CHECK( 2 == chunk.NPCR() );
  CHECK( 2 == chunk.numberPrecursorGroups() );
  CHECK( 2 == chunk.data().size() );

  decltype(auto) group1 = chunk.precursorGroup( 1 );
  CHECK( 2.3e-4 == Approx( group1.DEC() ) );
  CHECK( 2.3e-4 == Approx( group1.decayConstant() ) );

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
  CHECK( 1e-11 == Approx( group1.energies()[0] ) );
  CHECK( 1. == Approx( group1.energies()[1] ) );
  CHECK( 20. == Approx( group1.energies()[2] ) );

  CHECK( 3 == group1.probabilities().size() );
  CHECK( 1.2e-3 == Approx( group1.probabilities()[0] ) );
  CHECK( 2.5e-2 == Approx( group1.probabilities()[1] ) );
  CHECK( 1. == Approx( group1.probabilities()[2] ) );

  decltype(auto) group2 = chunk.precursorGroup( 2 );
  CHECK( 3.2e-4 == Approx( group2.DEC() ) );
  CHECK( 3.2e-4 == Approx( group2.decayConstant() ) );

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
  CHECK( 1e-11 == Approx( group2.energies()[0] ) );
  CHECK( 20. == Approx( group2.energies()[1] ) );

  CHECK( 2 == group2.probabilities().size() );
  CHECK( 2.4e-3 == Approx( group2.probabilities()[0] ) );
  CHECK( 2. == Approx( group2.probabilities()[1] ) );
}
