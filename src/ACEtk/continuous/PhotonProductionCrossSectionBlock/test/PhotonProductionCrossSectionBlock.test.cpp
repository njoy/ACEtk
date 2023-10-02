// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/PhotonProductionCrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PhotonProductionCrossSectionBlock = continuous::PhotonProductionCrossSectionBlock;
using PhotonProductionCrossSectionData = continuous::PhotonProductionCrossSectionData;
using TabulatedSecondaryParticleMultiplicity = continuous::TabulatedSecondaryParticleMultiplicity;
using PhotonProductionData = continuous::PhotonProductionData;

std::vector< double > chunk();
void verifyChunk( const PhotonProductionCrossSectionBlock& );

SCENARIO( "PhotonProductionCrossSectionBlock" ) {

  GIVEN( "valid data for a PhotonProductionCrossSectionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< PhotonProductionData > xs = {

        PhotonProductionCrossSectionData(
          1,
          {                    1.71740100000E+01, 1.21438600000E+01, 7.68045500000E+00,
            5.43090500000E+00, 3.84022400000E+00, 2.42878300000E+00, 1.71741500000E+00,
            1.21440300000E+00, 7.68079300000E-01, 5.43155100000E-01, 3.84154600000E-01,
            3.41606100000E-01, 2.43218100000E-01, 1.72502100000E-01, 1.23265800000E-01,
            7.76319400000E-02, 5.42665800000E-02, 3.83593600000E-02, 2.41345500000E-02,
            1.69157900000E-02, 1.19330400000E-02, 7.52588100000E-03, 5.30147700000E-03,
            3.74241900000E-03, 2.35974500000E-03, 1.66085400000E-03, 1.16578800000E-03,
            8.12732500000E-04, 7.21302100000E-04, 6.54483800000E-04, 5.59372400000E-04,
            4.93876600000E-04, 3.90771200000E-04, 3.28387200000E-04, 2.08326100000E-04,
            1.81663500000E-04, 1.55085200000E-04, 1.24126000000E-04, 1.03786200000E-04,
            7.45175200000E-05, 5.92842800000E-05, 4.46076700000E-05, 3.82766600000E-05,
            3.52914400000E-05, 3.38996200000E-05, 3.33423900000E-05, 3.32443400000E-05,
            3.34022300000E-05, 3.36990500000E-05, 3.44554600000E-05, 3.52169900000E-05,
            3.58729500000E-05, 3.63894900000E-05, 3.67662300000E-05, 3.70168600000E-05,
            3.71598700000E-05, 3.72143000000E-05, 3.71976900000E-05, 3.71253600000E-05,
            3.70102000000E-05, 3.68628700000E-05, 3.66920200000E-05, 3.65045600000E-05,
            3.63059900000E-05, 3.61006300000E-05, 3.58918300000E-05, 3.56821800000E-05,
            3.54736400000E-05, 3.52677000000E-05, 3.47705000000E-05, 3.43050800000E-05,
            3.38741800000E-05, 3.34769900000E-05, 3.31108400000E-05, 3.27723300000E-05,
            3.24578800000E-05, 3.21640000000E-05, 3.18874900000E-05, 3.16254500000E-05,
            3.13753100000E-05, 3.11348500000E-05, 3.09021400000E-05, 3.06755200000E-05,
            3.04536000000E-05, 3.02351800000E-05, 3.00192800000E-05, 2.98050700000E-05,
            2.95919000000E-05, 2.93792000000E-05, 2.91665600000E-05, 2.89536300000E-05,
            2.87401800000E-05, 2.85260300000E-05, 2.83110700000E-05, 2.80952300000E-05,
            2.78785100000E-05, 2.76609500000E-05, 2.74425900000E-05, 2.72235400000E-05 } ),
        TabulatedSecondaryParticleMultiplicity(
          12, 4,
          { 7.74238100000E-01,   8.00000000000E-01,   9.00000000000E-01,
            1.00000000000E+00,   1.09000000000E+00,   1.09000100000E+00,
            2.00000000000E+01 },
          { 0.00000000000E+00,   1.00000000000E-02,   7.11000000000E-02,
            1.19000000000E-01,   1.23300000000E-01,   0.00000000000E+00,
            0.00000000000E+00 } ) };

      PhotonProductionCrossSectionBlock chunk( std::move( xs ) );

      THEN( "a PhotonProductionCrossSectionBlock can be constructed and members "
            "can be tested" ) {

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

      PhotonProductionCrossSectionBlock chunk( xss.begin(), xss.begin() + 2,
                                               xss.end(), 2 );

      THEN( "a PhotonProductionCrossSectionBlock can be constructed and members "
            "can be tested" ) {

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

  return {

                    1,               103,
                   13,                 1,
                   99, 1.71740100000E+01, 1.21438600000E+01, 7.68045500000E+00,
    5.43090500000E+00, 3.84022400000E+00, 2.42878300000E+00, 1.71741500000E+00,
    1.21440300000E+00, 7.68079300000E-01, 5.43155100000E-01, 3.84154600000E-01,
    3.41606100000E-01, 2.43218100000E-01, 1.72502100000E-01, 1.23265800000E-01,
    7.76319400000E-02, 5.42665800000E-02, 3.83593600000E-02, 2.41345500000E-02,
    1.69157900000E-02, 1.19330400000E-02, 7.52588100000E-03, 5.30147700000E-03,
    3.74241900000E-03, 2.35974500000E-03, 1.66085400000E-03, 1.16578800000E-03,
    8.12732500000E-04, 7.21302100000E-04, 6.54483800000E-04, 5.59372400000E-04,
    4.93876600000E-04, 3.90771200000E-04, 3.28387200000E-04, 2.08326100000E-04,
    1.81663500000E-04, 1.55085200000E-04, 1.24126000000E-04, 1.03786200000E-04,
    7.45175200000E-05, 5.92842800000E-05, 4.46076700000E-05, 3.82766600000E-05,
    3.52914400000E-05, 3.38996200000E-05, 3.33423900000E-05, 3.32443400000E-05,
    3.34022300000E-05, 3.36990500000E-05, 3.44554600000E-05, 3.52169900000E-05,
    3.58729500000E-05, 3.63894900000E-05, 3.67662300000E-05, 3.70168600000E-05,
    3.71598700000E-05, 3.72143000000E-05, 3.71976900000E-05, 3.71253600000E-05,
    3.70102000000E-05, 3.68628700000E-05, 3.66920200000E-05, 3.65045600000E-05,
    3.63059900000E-05, 3.61006300000E-05, 3.58918300000E-05, 3.56821800000E-05,
    3.54736400000E-05, 3.52677000000E-05, 3.47705000000E-05, 3.43050800000E-05,
    3.38741800000E-05, 3.34769900000E-05, 3.31108400000E-05, 3.27723300000E-05,
    3.24578800000E-05, 3.21640000000E-05, 3.18874900000E-05, 3.16254500000E-05,
    3.13753100000E-05, 3.11348500000E-05, 3.09021400000E-05, 3.06755200000E-05,
    3.04536000000E-05, 3.02351800000E-05, 3.00192800000E-05, 2.98050700000E-05,
    2.95919000000E-05, 2.93792000000E-05, 2.91665600000E-05, 2.89536300000E-05,
    2.87401800000E-05, 2.85260300000E-05, 2.83110700000E-05, 2.80952300000E-05,
    2.78785100000E-05, 2.76609500000E-05, 2.74425900000E-05, 2.72235400000E-05,
                   12,                 4,                 0,                 7,
    7.74238100000E-01, 8.00000000000E-01, 9.00000000000E-01, 1.00000000000E+00,
    1.09000000000E+00, 1.09000100000E+00, 2.00000000000E+01, 0.00000000000E+00,
    1.00000000000E-02, 7.11000000000E-02, 1.19000000000E-01, 1.23300000000E-01,
    0.00000000000E+00, 0.00000000000E+00
  };
}

void verifyChunk( const PhotonProductionCrossSectionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 122 == chunk.length() );
  CHECK( "SIGP" == chunk.name() );

  CHECK( 2 == chunk.NTRP() );
  CHECK( 2 == chunk.numberPhotonProductionReactions() );
  CHECK( 2 == chunk.data().size() );

  CHECK( 1 == chunk.LSIG(1) );
  CHECK( 103 == chunk.LSIG(2) );
  CHECK( 1 == chunk.crossSectionLocator(1) );
  CHECK( 103 == chunk.crossSectionLocator(2) );

  CHECK( true == std::holds_alternative< PhotonProductionCrossSectionData >( chunk.crossSectionData(1) ) );
  CHECK( true == std::holds_alternative< TabulatedSecondaryParticleMultiplicity >( chunk.crossSectionData(2) ) );

  auto xs1 = std::get< PhotonProductionCrossSectionData >( chunk.crossSectionData(1) );
  CHECK( 13 == xs1.MFTYPE() );
  CHECK( 13 == xs1.type() );
  CHECK( 1 == xs1.energyIndex() );
  CHECK( 99 == xs1.numberValues() );
  CHECK( 99 == xs1.crossSections().size() );
  CHECK_THAT( 17.17401, WithinRel( xs1.crossSections().front() ) );
  CHECK_THAT( 2.72235400000E-05, WithinRel( xs1.crossSections().back() ) );

  auto xs2 = std::get< TabulatedSecondaryParticleMultiplicity >( chunk.crossSectionData(2) );
  CHECK( 12 == xs2.MFTYPE() );
  CHECK( 12 == xs2.type() );
  CHECK( 4 == xs2.MT() );
  CHECK( 4 == xs2.reactionNumber() );
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
  CHECK( 7 == xs2.NE() );
  CHECK( 7 == xs2.numberValues() );
  CHECK( 7 == xs2.energies().size() );
  CHECK_THAT( 0.7742381, WithinRel( xs2.energies().front() ) );
  CHECK_THAT( 1., WithinRel( xs2.energies()[3] ) );
  CHECK_THAT( 20., WithinRel( xs2.energies().back() ) );
  CHECK( 7 == xs2.multiplicities().size() );
  CHECK_THAT( 0., WithinRel( xs2.multiplicities().front() ) );
  CHECK_THAT( 0.119, WithinRel( xs2.multiplicities()[3] ) );
  CHECK_THAT( 0., WithinRel( xs2.multiplicities().back() ) );
}
