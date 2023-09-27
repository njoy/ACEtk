#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/electron/TabulatedAngularDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedAngularDistribution = electron::TabulatedAngularDistribution;

std::vector< double > chunk();
void verifyChunk( const TabulatedAngularDistribution& );

SCENARIO( "TabulatedAngularDistribution" ) {

  GIVEN( "valid data for a TabulatedAngularDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 1000.;
      std::vector< double > cosines = { -1., 0., 1. };
      std::vector< double > cdf = { 0., 0.75, 1. };

      TabulatedAngularDistribution chunk( energy, std::move( cosines ),
                                                  std::move( cdf ) );

      THEN( "a PhotoatomicElectronShellBlock can be constructed and members can "
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

      TabulatedAngularDistribution chunk( 1000., xss.begin(), xss.end(), 3 );

      THEN( "a PhotoatomicElectronShellBlock can be constructed and members can "
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
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { -1., 0., 1.,
            0., 0.75, 1. };
}

void verifyChunk( const TabulatedAngularDistribution& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 6 == chunk.length() );
  CHECK( "TabulatedAngularDistribution" == chunk.name() );

  CHECK( 1000. == Approx( chunk.energy() ) );

  CHECK( 3 == chunk.LA() );
  CHECK( 3 == chunk.numberCosines() );

  CHECK( 3 == chunk.cosines().size() );
  CHECK( 3 == chunk.cdf().size() );

  CHECK( -1. == Approx( chunk.cosines()[0] ) );
  CHECK(  0. == Approx( chunk.cosines()[1] ) );
  CHECK(  1. == Approx( chunk.cosines()[2] ) );

  CHECK(  0.   == Approx( chunk.cdf()[0] ) );
  CHECK(  0.75 == Approx( chunk.cdf()[1] ) );
  CHECK(  1.   == Approx( chunk.cdf()[2] ) );
}
