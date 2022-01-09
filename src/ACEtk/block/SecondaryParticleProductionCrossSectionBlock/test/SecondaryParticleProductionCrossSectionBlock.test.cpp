#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/SecondaryParticleProductionCrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using SecondaryParticleProductionCrossSectionBlock = block::SecondaryParticleProductionCrossSectionBlock;
using TabulatedSecondaryParticleMultiplicity = block::TabulatedSecondaryParticleMultiplicity;

std::vector< double > chunk();
void verifyChunk( const SecondaryParticleProductionCrossSectionBlock& );

SCENARIO( "SecondaryParticleProductionCrossSectionBlock" ) {

  GIVEN( "valid data for a SecondaryParticleProductionCrossSectionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< TabulatedSecondaryParticleMultiplicity > xs = {

        TabulatedSecondaryParticleMultiplicity(
          12, 4,
          { 7.74238100000E-01,   8.00000000000E-01,   9.00000000000E-01,
            1.00000000000E+00,   1.09000000000E+00,   1.09000100000E+00,
            2.00000000000E+01 },
          { 0.00000000000E+00,   1.00000000000E-02,   7.11000000000E-02,
            1.19000000000E-01,   1.23300000000E-01,   0.00000000000E+00,
            0.00000000000E+00 } ),
        TabulatedSecondaryParticleMultiplicity(
          12, 102,
          { 1.00000000000E-05,   2.00000000000E+01 },
          { 1.00000000000E+00,   1.00000000000E+00 } ) };

      SecondaryParticleProductionCrossSectionBlock chunk( std::move( xs ) );

      THEN( "a SecondaryParticleProductionCrossSectionBlock can be constructed and members "
            "can be tested" ) {

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

      SecondaryParticleProductionCrossSectionBlock chunk( xss.begin(), xss.begin() + 2,
                                               xss.end(), 2 );

      THEN( "a SecondaryParticleProductionCrossSectionBlock can be constructed and members "
            "can be tested" ) {

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

  return {
                    1,                19,
                   12,                 4,                 0,                 7,
    7.74238100000E-01, 8.00000000000E-01, 9.00000000000E-01, 1.00000000000E+00,
    1.09000000000E+00, 1.09000100000E+00, 2.00000000000E+01, 0.00000000000E+00,
    1.00000000000E-02, 7.11000000000E-02, 1.19000000000E-01, 1.23300000000E-01,
    0.00000000000E+00, 0.00000000000E+00,
                   12,               102,                 0,                 2,
    1.00000000000E-05, 2.00000000000E+01, 1.00000000000E+00,   1.00000000000E+00
  };
}

void verifyChunk( const SecondaryParticleProductionCrossSectionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 28 == chunk.length() );
  CHECK( "SIGH" == chunk.name() );

  CHECK( 2 == chunk.NP() );
  CHECK( 2 == chunk.numberSecondaryParticleProductionReactions() );
  CHECK( 2 == chunk.data().size() );

  CHECK( 1 == chunk.LSIG(1) );
  CHECK( 19 == chunk.LSIG(2) );
  CHECK( 1 == chunk.crossSectionLocator(1) );
  CHECK( 19 == chunk.crossSectionLocator(2) );

  auto xs1 = chunk.crossSectionData(1);
  CHECK( 12 == xs1.MFTYPE() );
  CHECK( 12 == xs1.type() );
  CHECK( 4 == xs1.MT() );
  CHECK( 4 == xs1.reactionNumber() );
  CHECK( 0 == xs1.interpolationData().NB() );
  CHECK( 0 == xs1.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == xs1.interpolationData().INT().size() );
  CHECK( 0 == xs1.interpolationData().interpolants().size() );
  CHECK( 0 == xs1.interpolationData().NBT().size() );
  CHECK( 0 == xs1.interpolationData().boundaries().size() );
  CHECK( 0 == xs1.NB() );
  CHECK( 0 == xs1.numberInterpolationRegions() );
  CHECK( 0 == xs1.INT().size() );
  CHECK( 0 == xs1.interpolants().size() );
  CHECK( 0 == xs1.NBT().size() );
  CHECK( 0 == xs1.boundaries().size() );
  CHECK( 7 == xs1.NE() );
  CHECK( 7 == xs1.numberValues() );
  CHECK( 7 == xs1.energies().size() );
  CHECK( 0.7742381 == Approx( xs1.energies().front() ) );
  CHECK( 1. == Approx( xs1.energies()[3] ) );
  CHECK( 20. == Approx( xs1.energies().back() ) );
  CHECK( 7 == xs1.multiplicities().size() );
  CHECK( 0. == Approx( xs1.multiplicities().front() ) );
  CHECK( 0.119 == Approx( xs1.multiplicities()[3] ) );
  CHECK( 0. == Approx( xs1.multiplicities().back() ) );

  auto xs2 = chunk.crossSectionData(2);
  CHECK( 12 == xs2.MFTYPE() );
  CHECK( 12 == xs2.type() );
  CHECK( 102 == xs2.MT() );
  CHECK( 102 == xs2.reactionNumber() );
  CHECK( 0 == xs2.interpolationData().NB() );
  CHECK( 0 == xs2.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == xs2.interpolationData().INT().size() );
  CHECK( 0 == xs2.interpolationData().interpolants().size() );
  CHECK( 0 == xs2.interpolationData().NBT().size() );
  CHECK( 0 == xs2.interpolationData().boundaries().size() );
  CHECK( 0 == xs2.NB() );
  CHECK( 0 == xs2.numberInterpolationRegions() );
  CHECK( 0 == xs2.INT().size() );
  CHECK( 0 == xs2.interpolants().size() );
  CHECK( 0 == xs2.NBT().size() );
  CHECK( 0 == xs2.boundaries().size() );
  CHECK( 2 == xs2.NE() );
  CHECK( 2 == xs2.numberValues() );
  CHECK( 2 == xs2.energies().size() );
  CHECK( 1e-5 == Approx( xs2.energies().front() ) );
  CHECK( 20. == Approx( xs2.energies().back() ) );
  CHECK( 2 == xs2.multiplicities().size() );
  CHECK( 1. == Approx( xs2.multiplicities().front() ) );
  CHECK( 1. == Approx( xs2.multiplicities().back() ) );
}
