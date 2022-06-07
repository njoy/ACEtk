#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/PhotoAtomicComptonProfile.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PhotoAtomicComptonProfile = block::PhotoAtomicComptonProfile;

std::vector< double > chunk();
void verifyChunk( const PhotoAtomicComptonProfile& );

SCENARIO( "PhotoAtomicComptonProfile" ) {

  GIVEN( "valid data for a PhotoAtomicComptonProfile instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      int interpolation = 2;
      std::vector< double > momentum = { 1e-11, 1.0, 20.0 };
      std::vector< double > pdf = { 0.5, 0.5, 0.5 };
      std::vector< double > cdf = { 0.0, 0.5, 1.0 };

      PhotoAtomicComptonProfile chunk( interpolation,
                                       std::move( momentum ),
                                       std::move( pdf ),
                                       std::move( cdf ) );

      THEN( "a PhotoAtomicComptonProfile can be constructed and "
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

      PhotoAtomicComptonProfile chunk( xss.begin(), xss.end() );

      THEN( "a PhotoAtomicComptonProfile can be constructed and "
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

  return {                 2,                  3,  1.00000000000E-11,  1.00000000000E+00,
           2.00000000000E+01,  0.50000000000E+00,  0.50000000000E+00,  0.50000000000E+00,
           0.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00 };
}

void verifyChunk( const PhotoAtomicComptonProfile& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 11 == chunk.length() );
  CHECK( "PhotoAtomicComptonProfile" == chunk.name() );

  CHECK( 2 == chunk.interpolation() );
  CHECK( 3 == chunk.numberValues() );

  CHECK( 3 == chunk.momentum().size() );
  CHECK( 1e-11 == Approx( chunk.momentum().front() ) );
  CHECK( 20. == Approx( chunk.momentum().back() ) );

  CHECK( 3 == chunk.pdf().size() );
  CHECK( .5 == Approx( chunk.pdf().front() ) );
  CHECK( .5 == Approx( chunk.pdf().back() ) );

  CHECK( 3 == chunk.cdf().size() );
  CHECK( 0. == Approx( chunk.cdf().front() ) );
  CHECK( 1. == Approx( chunk.cdf().back() ) );
}
