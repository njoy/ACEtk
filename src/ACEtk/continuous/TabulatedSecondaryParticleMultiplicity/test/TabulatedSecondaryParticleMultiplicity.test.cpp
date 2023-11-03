#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/continuous/TabulatedSecondaryParticleMultiplicity.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedSecondaryParticleMultiplicity = continuous::TabulatedSecondaryParticleMultiplicity;

std::vector< double > chunk();
void verifyChunk( const TabulatedSecondaryParticleMultiplicity& );

SCENARIO( "TabulatedSecondaryParticleMultiplicity" ) {

  GIVEN( "valid data for a TabulatedSecondaryParticleMultiplicity instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      unsigned int mftype = 12;
      unsigned int mt = 4;
      std::vector< double > energies = {
          7.74238100000E-01,   8.00000000000E-01,   9.00000000000E-01,
          1.00000000000E+00,   1.09000000000E+00,   1.09000100000E+00,
          2.00000000000E+01 };
      std::vector< double > multiplicities = {
          0.00000000000E+00,   1.00000000000E-02,   7.11000000000E-02,
          1.19000000000E-01,   1.23300000000E-01,   0.00000000000E+00,
          0.00000000000E+00 };

      TabulatedSecondaryParticleMultiplicity chunk( mftype, mt,
                                                    std::move( energies ),
                                                    std::move( multiplicities ) );

      THEN( "a TabulatedSecondaryParticleMultiplicity can be constructed and "
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

      TabulatedSecondaryParticleMultiplicity chunk( xss.begin(), xss.end() );

      THEN( "a TabulatedSecondaryParticleMultiplicity can be constructed and "
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

  return {                 12,                   4,                   0,                   7,
            7.74238100000E-01,   8.00000000000E-01,   9.00000000000E-01,   1.00000000000E+00,
            1.09000000000E+00,   1.09000100000E+00,   2.00000000000E+01,   0.00000000000E+00,
            1.00000000000E-02,   7.11000000000E-02,   1.19000000000E-01,   1.23300000000E-01,
            0.00000000000E+00,   0.00000000000E+00 };
}

void verifyChunk( const TabulatedSecondaryParticleMultiplicity& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 18 == chunk.length() );
  CHECK( "TabulatedSecondaryParticleMultiplicity" == chunk.name() );

  CHECK( 12 == chunk.MFTYPE() );
  CHECK( 12 == chunk.type() );
  CHECK( 4 == chunk.MT() );
  CHECK( 4 == chunk.reactionNumber() );

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

  CHECK( 7 == chunk.NE() );
  CHECK( 7 == chunk.numberValues() );

  CHECK( 7 == chunk.energies().size() );
  CHECK( 0.7742381 == Approx( chunk.energies().front() ) );
  CHECK( 1. == Approx( chunk.energies()[3] ) );
  CHECK( 20. == Approx( chunk.energies().back() ) );

  CHECK( 7 == chunk.multiplicities().size() );
  CHECK( 0. == Approx( chunk.multiplicities().front() ) );
  CHECK( 0.119 == Approx( chunk.multiplicities()[3] ) );
  CHECK( 0. == Approx( chunk.multiplicities().back() ) );
}
