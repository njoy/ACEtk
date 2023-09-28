#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/dosimetry/CrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using DosimetryCrossSectionBlock = block::DosimetryCrossSectionBlock;
using DosimetryCrossSectionData = block::DosimetryCrossSectionData;

std::vector< double > chunk();
void verifyChunk( const DosimetryCrossSectionBlock& );

SCENARIO( "DosimetryCrossSectionBlock" ) {

  GIVEN( "valid data for a DosimetryCrossSectionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< DosimetryCrossSectionData > xs = {

        DosimetryCrossSectionData(
          { 1.896100000000E+00,  2.000000000000E+00,
            2.050000000000E+00,  2.000000000000E+01 },
          { 0.000000000000E+00,  9.090000000000E-15,
            3.638500000000E-02,  3.220000000000E-02 } ),
        DosimetryCrossSectionData(
          { 3.248700000000E+00,  3.600000000000E+00,  2.000000000000E+01 },
          { 0.000000000000E+00,  5.653700000000E-02,  4.980000000000E-02 } ) };

      DosimetryCrossSectionBlock chunk( std::move( xs ) );

      THEN( "a DosimetryCrossSectionBlock can be constructed and members can be tested" ) {

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

      DosimetryCrossSectionBlock chunk( xss.begin(), xss.begin() + 2, xss.end(), 2 );

      THEN( "a DosimetryCrossSectionBlock can be constructed and members can be tested" ) {

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

                    1,                  11,
                    0,                   4,  1.896100000000E+00,  2.000000000000E+00,
   2.050000000000E+00,  2.000000000000E+01,  0.000000000000E+00,  9.090000000000E-15,
   3.638500000000E-02,  3.220000000000E-02,                   0,                   3,
   3.248700000000E+00,  3.600000000000E+00,  2.000000000000E+01,  0.000000000000E+00,
   5.653700000000E-02,  4.980000000000E-02 };
}

void verifyChunk( const DosimetryCrossSectionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 20 == chunk.length() );
  CHECK( "SIGD" == chunk.name() );

  CHECK( 2 == chunk.NTR() );
  CHECK( 2 == chunk.numberReactions() );

  CHECK( 1 == chunk.LSIG(1) );
  CHECK( 11 == chunk.LSIG(2) );
  CHECK( 1 == chunk.crossSectionLocator(1) );
  CHECK( 11 == chunk.crossSectionLocator(2) );

  auto xs = chunk.crossSectionData(1);
  CHECK( 0 == xs.NB() );
  CHECK( 4 == xs.numberEnergyPoints() );
  CHECK( 4 == xs.energies().size() );
  CHECK( 4 == xs.crossSections().size() );
  CHECK( 1.8961 == Approx( xs.energies().front() ) );
  CHECK( 20. == Approx( xs.energies().back() ) );
  CHECK( 0. == Approx( xs.crossSections().front() ) );
  CHECK( 0.0322 == Approx( xs.crossSections().back() ) );

  xs = chunk.crossSectionData(2);
  CHECK( 0 == xs.NB() );
  CHECK( 3 == xs.numberEnergyPoints() );
  CHECK( 3 == xs.energies().size() );
  CHECK( 3 == xs.crossSections().size() );
  CHECK( 3.2487 == Approx( xs.energies().front() ) );
  CHECK( 20. == Approx( xs.energies().back() ) );
  CHECK( 0. == Approx( xs.crossSections().front() ) );
  CHECK( 0.0498 == Approx( xs.crossSections().back() ) );
}
