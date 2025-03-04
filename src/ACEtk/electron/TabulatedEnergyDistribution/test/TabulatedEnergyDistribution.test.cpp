// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/TabulatedEnergyDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedEnergyDistribution = electron::TabulatedEnergyDistribution;

std::vector< double > chunk();
void verifyChunk( const TabulatedEnergyDistribution&, const std::vector< double >& );
TabulatedEnergyDistribution makeDummyBlock();

SCENARIO( "TabulatedEnergyDistribution" ) {

  GIVEN( "valid data for a TabulatedEnergyDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 1000.;
      std::vector< double > outgoing = { 10., 100., 999. };
      std::vector< double > cdf = { 0., 0.75, 1. };

      TabulatedEnergyDistribution chunk( energy, std::move( outgoing ),
                                                 std::move( cdf ) );

      THEN( "a TabulatedEnergyDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      TabulatedEnergyDistribution chunk( 1000., xss.begin(), xss.end(), 3 );

      THEN( "a TabulatedEnergyDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      TabulatedEnergyDistribution chunk( 1000., xss.begin(), xss.end(), 3 );
      TabulatedEnergyDistribution copy( chunk );

      THEN( "an TabulatedEnergyDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      TabulatedEnergyDistribution chunk( 1000., xss.begin(), xss.end(), 3 );
      TabulatedEnergyDistribution move( std::move( chunk ) );

      THEN( "an TabulatedEnergyDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      TabulatedEnergyDistribution chunk( 1000., xss.begin(), xss.end(), 3 );
      TabulatedEnergyDistribution copy = makeDummyBlock();
      copy = chunk;

      THEN( "an TabulatedEnergyDistribution can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      TabulatedEnergyDistribution chunk( 1000., xss.begin(), xss.end(), 3 );
      TabulatedEnergyDistribution move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an TabulatedEnergyDistribution can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 10., 100., 999.,
            0., 0.75, 1. };
}

void verifyChunk( const TabulatedEnergyDistribution& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 6 == chunk.length() );
  CHECK( "TabulatedEnergyDistribution" == chunk.name() );

  CHECK_THAT( 1000., WithinRel( chunk.energy() ) );

  CHECK( 3 == chunk.LB() );
  CHECK( 3 == chunk.numberOutgoingEnergies() );

  CHECK( 3 == chunk.outgoingEnergies().size() );
  CHECK( 3 == chunk.cdf().size() );

  CHECK_THAT(  10., WithinRel( chunk.outgoingEnergies()[0] ) );
  CHECK_THAT( 100., WithinRel( chunk.outgoingEnergies()[1] ) );
  CHECK_THAT( 999., WithinRel( chunk.outgoingEnergies()[2] ) );

  CHECK_THAT(  0.  , WithinRel( chunk.cdf()[0] ) );
  CHECK_THAT(  0.75, WithinRel( chunk.cdf()[1] ) );
  CHECK_THAT(  1.  , WithinRel( chunk.cdf()[2] ) );
}

TabulatedEnergyDistribution makeDummyBlock() {

  return { 1, { 0., 1. }, { 0.5, 0.5 } };
}
