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
void verifyChunk( const TabulatedAngularDistribution&, const std::vector< double >& );
TabulatedAngularDistribution makeDummyBlock();

SCENARIO( "TabulatedAngularDistribution" ) {

  GIVEN( "valid data for a TabulatedAngularDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 1000.;
      std::vector< double > cosines = { -1., 0., 1. };
      std::vector< double > cdf = { 0., 0.75, 1. };

      TabulatedAngularDistribution chunk( energy, std::move( cosines ),
                                                  std::move( cdf ) );

      THEN( "a TabulatedAngularDistribution can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      TabulatedAngularDistribution chunk( 1000., xss.begin(), xss.end(), 3 );

      THEN( "a TabulatedAngularDistribution can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      TabulatedAngularDistribution chunk( 1000., xss.begin(), xss.end(), 3 );
      TabulatedAngularDistribution copy( chunk );

      THEN( "an TabulatedAngularDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      TabulatedAngularDistribution chunk( 1000., xss.begin(), xss.end(), 3 );
      TabulatedAngularDistribution move( std::move( chunk ) );

      THEN( "an TabulatedAngularDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      TabulatedAngularDistribution chunk( 1000., xss.begin(), xss.end(), 3 );
      TabulatedAngularDistribution copy = makeDummyBlock();
      copy = chunk;

      THEN( "an TabulatedAngularDistribution can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      TabulatedAngularDistribution chunk( 1000., xss.begin(), xss.end(), 3 );
      TabulatedAngularDistribution move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an TabulatedAngularDistribution can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { -1., 0., 1.,
            0., 0.75, 1. };
}

void verifyChunk( const TabulatedAngularDistribution& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

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

TabulatedAngularDistribution makeDummyBlock() {

  return { 1, { -1., 1. }, { 0.5, 0.5 } };
}
