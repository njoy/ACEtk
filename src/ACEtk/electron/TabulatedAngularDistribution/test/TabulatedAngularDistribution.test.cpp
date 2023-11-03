// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
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

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
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

  CHECK_THAT( 1000., WithinRel( chunk.energy() ) );

  CHECK( 3 == chunk.LA() );
  CHECK( 3 == chunk.numberCosines() );

  CHECK( 3 == chunk.cosines().size() );
  CHECK( 3 == chunk.cdf().size() );

  CHECK_THAT( -1., WithinRel( chunk.cosines()[0] ) );
  CHECK_THAT(  0., WithinRel( chunk.cosines()[1] ) );
  CHECK_THAT(  1., WithinRel( chunk.cosines()[2] ) );

  CHECK_THAT(  0.  , WithinRel( chunk.cdf()[0] ) );
  CHECK_THAT(  0.75, WithinRel( chunk.cdf()[1] ) );
  CHECK_THAT(  1.  , WithinRel( chunk.cdf()[2] ) );
}
