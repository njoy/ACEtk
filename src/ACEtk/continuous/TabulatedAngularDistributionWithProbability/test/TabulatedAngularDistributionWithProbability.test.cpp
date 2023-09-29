#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/continuous/TabulatedAngularDistributionWithProbability.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedAngularDistributionWithProbability = block::TabulatedAngularDistributionWithProbability;

std::vector< double > chunk();
void verifyChunk( const TabulatedAngularDistributionWithProbability& );

SCENARIO( "TabulatedAngularDistributionWithProbability" ) {

  GIVEN( "valid data for a TabulatedAngularDistributionWithProbability instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 2.1;
      double pdf = 0.5;
      double cdf = 0.75;
      int interpolation = 2;
      std::vector< double > cosines = { -1.0, 0.0, 1.0 };
      std::vector< double > pdfs = { 0.5, 0.5, 0.5 };
      std::vector< double > cdfs = { 0.0, 0.5, 1.0 };

      TabulatedAngularDistributionWithProbability chunk( energy, pdf, cdf,
                                                         interpolation,
                                                         std::move( cosines ),
                                                         std::move( pdfs ),
                                                         std::move( cdfs ) );

      THEN( "a TabulatedAngularDistributionWithProbability can be constructed and members can "
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

      double energy = 2.1;
      double pdf = 0.5;
      double cdf = 0.75;
      TabulatedAngularDistributionWithProbability chunk( energy, pdf, cdf,
                                                         xss.begin(), xss.end() );

      THEN( "a TabulatedAngularDistributionWithProbability can be constructed and members can be tested" ) {

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

  return {                 2,                  3, -1.00000000000E+00,  0.00000000000E+00,
           1.00000000000E+00,  0.50000000000E+00,  0.50000000000E+00,  0.50000000000E+00,
           0.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00 };
}

void verifyChunk( const TabulatedAngularDistributionWithProbability& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 11 == chunk.length() );
  CHECK( "TabulatedAngularDistribution" == chunk.name() );

  CHECK( 2.1 == Approx( chunk.energy() ) );
  CHECK( .5 == Approx( chunk.probability() ) );
  CHECK( .75 == Approx( chunk.cumulativeProbability() ) );
  CHECK( 2 == chunk.interpolation() );
  CHECK( 3 == chunk.numberCosines() );

  CHECK( 3 == chunk.cosines().size() );
  CHECK( -1. == Approx( chunk.cosines().front() ) );
  CHECK( +1. == Approx( chunk.cosines().back() ) );

  CHECK( 3 == chunk.pdf().size() );
  CHECK( .5 == Approx( chunk.pdf().front() ) );
  CHECK( .5 == Approx( chunk.pdf().back() ) );

  CHECK( 3 == chunk.cdf().size() );
  CHECK( 0. == Approx( chunk.cdf().front() ) );
  CHECK( 1. == Approx( chunk.cdf().back() ) );
}
