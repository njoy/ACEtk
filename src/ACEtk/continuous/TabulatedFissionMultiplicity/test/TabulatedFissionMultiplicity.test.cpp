#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/continuous/TabulatedFissionMultiplicity.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedFissionMultiplicity = continuous::TabulatedFissionMultiplicity;

std::vector< double > chunk();
void verifyChunk( const TabulatedFissionMultiplicity& );

SCENARIO( "TabulatedFissionMultiplicity" ) {

  GIVEN( "valid data for a TabulatedFissionMultiplicity instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 1e-5, 1., 20. };
      std::vector< double > multiplicities = { 2.35, 2.55, 7. };

      TabulatedFissionMultiplicity chunk( std::move( energies ),
                                          std::move( multiplicities ) );

      THEN( "a TabulatedFissionMultiplicity can be constructed and "
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

      TabulatedFissionMultiplicity chunk( xss.begin(), xss.end() );

      THEN( "a TabulatedFissionMultiplicity can be constructed and "
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

  return {                  2,                   0,                   3,
            1.00000000000E-11,   1.00000000000E+00,   2.00000000000E+01,   2.35000000000E+00,
            2.55000000000E+00,   7.00000000000E+00 };
}

void verifyChunk( const TabulatedFissionMultiplicity& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 9 == chunk.length() );
  CHECK( "TabulatedFissionMultiplicity" == chunk.name() );

  CHECK( 2 == chunk.LNU() );
  CHECK( 2 == chunk.type() );

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

  CHECK( 3 == chunk.multiplicities().size() );
  CHECK( 2.35 == Approx( chunk.multiplicities()[0] ) );
  CHECK( 2.55 == Approx( chunk.multiplicities()[1] ) );
  CHECK( 7. == Approx( chunk.multiplicities()[2] ) );
}
