#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/TabulatedKalbachMannDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedKalbachMannDistribution = block::TabulatedKalbachMannDistribution;

std::vector< double > chunk();
void verifyChunk( const TabulatedKalbachMannDistribution& );

SCENARIO( "TabulatedKalbachMannDistribution" ) {

  GIVEN( "valid data for a TabulatedKalbachMannDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double incident = 2.1;
      int interpolation = 2;
      std::size_t discrete = 3;
      std::vector< double > cosines = { 1e-11, 1.0, 20.0 };
      std::vector< double > pdf = { 0.5, 0.5, 0.5 };
      std::vector< double > cdf = { 0.0, 0.5, 1.0 };
      std::vector< double > r = { 1., 2., 3. };
      std::vector< double > a = { 4., 5., 6. };

      TabulatedKalbachMannDistribution chunk( incident, interpolation,
                                              std::move( cosines ),
                                              std::move( pdf ),
                                              std::move( cdf ),
                                              std::move( r ),
                                              std::move( a ),
                                              discrete );

      THEN( "a TabulatedKalbachMannDistribution can be constructed and "
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

      double incident = 2.1;
      TabulatedKalbachMannDistribution chunk( incident, xss.begin(), xss.end() );

      THEN( "a TabulatedKalbachMannDistribution can be constructed and "
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

  return {                32,                  3,  1.00000000000E-11,  1.00000000000E+00,
           2.00000000000E+01,  0.50000000000E+00,  0.50000000000E+00,  0.50000000000E+00,
           0.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00,  1.00000000000E+00,
           2.00000000000E+00,  3.00000000000E+00,  4.00000000000E+00,  5.00000000000E+00,
           6.00000000000E+00 };
}

void verifyChunk( const TabulatedKalbachMannDistribution& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 17 == chunk.length() );
  CHECK( "DLW::TabulatedKalbachMannDistribution" == chunk.name() );

  CHECK( 2.1 == Approx( chunk.incidentEnergy() ) );
  CHECK( 2 == chunk.interpolation() );
  CHECK( 3 == chunk.numberDiscretePhotonLines() );
  CHECK( 3 == chunk.numberOutgoingEnergies() );

  CHECK( 3 == chunk.outgoingEnergies().size() );
  CHECK( 1e-11 == Approx( chunk.outgoingEnergies().front() ) );
  CHECK( 20. == Approx( chunk.outgoingEnergies().back() ) );

  CHECK( 3 == chunk.pdf().size() );
  CHECK( .5 == Approx( chunk.pdf().front() ) );
  CHECK( .5 == Approx( chunk.pdf().back() ) );

  CHECK( 3 == chunk.cdf().size() );
  CHECK( 0. == Approx( chunk.cdf().front() ) );
  CHECK( 1. == Approx( chunk.cdf().back() ) );

  CHECK( 3 == chunk.precompoundFractionValues().size() );
  CHECK( 1. == Approx( chunk.precompoundFractionValues().front() ) );
  CHECK( 3. == Approx( chunk.precompoundFractionValues().back() ) );

  CHECK( 3 == chunk.cdf().size() );
  CHECK( 4. == Approx( chunk.angularDistributionSlopeValues().front() ) );
  CHECK( 6. == Approx( chunk.angularDistributionSlopeValues().back() ) );
}
