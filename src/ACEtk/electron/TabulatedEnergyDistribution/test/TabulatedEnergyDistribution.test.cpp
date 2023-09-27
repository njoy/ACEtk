#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/electron/TabulatedEnergyDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedEnergyDistribution = electron::TabulatedEnergyDistribution;

std::vector< double > chunk();
void verifyChunk( const TabulatedEnergyDistribution& );

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

      TabulatedEnergyDistribution chunk( 1000., xss.begin(), xss.end(), 3 );

      THEN( "a TabulatedEnergyDistribution can be constructed and "
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

  return { 10., 100., 999.,
            0., 0.75, 1. };
}

void verifyChunk( const TabulatedEnergyDistribution& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 6 == chunk.length() );
  CHECK( "TabulatedEnergyDistribution" == chunk.name() );

  CHECK( 1000. == Approx( chunk.energy() ) );

  CHECK( 3 == chunk.LB() );
  CHECK( 3 == chunk.numberOutgoingEnergies() );

  CHECK( 3 == chunk.outgoingEnergies().size() );
  CHECK( 3 == chunk.cdf().size() );

  CHECK(  10. == Approx( chunk.outgoingEnergies()[0] ) );
  CHECK( 100. == Approx( chunk.outgoingEnergies()[1] ) );
  CHECK( 999. == Approx( chunk.outgoingEnergies()[2] ) );

  CHECK(  0.   == Approx( chunk.cdf()[0] ) );
  CHECK(  0.75 == Approx( chunk.cdf()[1] ) );
  CHECK(  1.   == Approx( chunk.cdf()[2] ) );
}