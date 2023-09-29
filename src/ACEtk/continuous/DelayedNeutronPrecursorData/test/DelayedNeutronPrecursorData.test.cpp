#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/continuous/DelayedNeutronPrecursorData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using DelayedNeutronPrecursorData = block::DelayedNeutronPrecursorData;

std::vector< double > chunk();
void verifyChunk( const DelayedNeutronPrecursorData& );

SCENARIO( "DelayedNeutronPrecursorData" ) {

  GIVEN( "valid data for a DelayedNeutronPrecursorData instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      unsigned int number = 1;
      double lambda = 2.3e-4;
      std::vector< double > energies = { 1e-5, 1., 20. };
      std::vector< double > probabilities = { 1.2e-3, 2.5e-2, 1. };

      DelayedNeutronPrecursorData chunk( number, lambda,
                                         std::move( energies ),
                                         std::move( probabilities ) );

      THEN( "a DelayedNeutronPrecursorData can be constructed and members can "
            "be tested" ) {

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

      DelayedNeutronPrecursorData chunk( xss.begin(), xss.end(), 1 );

      THEN( "a DelayedNeutronPrecursorData can be constructed and "
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
            2.50000000000E-02,   1.00000000000E+00 };
}

void verifyChunk( const DelayedNeutronPrecursorData& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 9 == chunk.length() );
  CHECK( "DelayedNeutronPrecursorData" == chunk.name() );

  CHECK( 1 == chunk.number() );

  CHECK( 2.3e-4 == Approx( chunk.DEC() ) );
  CHECK( 2.3e-4 == Approx( chunk.decayConstant() ) );

  CHECK( 0 == chunk.interpolationData().NB() );
  CHECK( 0 == chunk.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == chunk.interpolationData().INT().size() );
  CHECK( 0 == chunk.interpolationData().interpolants().size() );
  CHECK( 0 == chunk.interpolationData().NBT().size() );
  CHECK( 0 == chunk.interpolationData().boundaries().size() );

  CHECK( 0 == chunk.NB() );
  CHECK( 0 == chunk.numberInterpolationRegions() );
  CHECK( 0 == chunk.INT().size() );
  CHECK( 0 == chunk.interpolants().size() );
  CHECK( 0 == chunk.NBT().size() );
  CHECK( 0 == chunk.boundaries().size() );

  CHECK( 3 == chunk.NE() );
  CHECK( 3 == chunk.numberValues() );

  CHECK( 3 == chunk.energies().size() );
  CHECK( 1e-11 == Approx( chunk.energies()[0] ) );
  CHECK( 1. == Approx( chunk.energies()[1] ) );
  CHECK( 20. == Approx( chunk.energies()[2] ) );

  CHECK( 3 == chunk.probabilities().size() );
  CHECK( 1.2e-3 == Approx( chunk.probabilities()[0] ) );
  CHECK( 2.5e-2 == Approx( chunk.probabilities()[1] ) );
  CHECK( 1. == Approx( chunk.probabilities()[2] ) );
}
