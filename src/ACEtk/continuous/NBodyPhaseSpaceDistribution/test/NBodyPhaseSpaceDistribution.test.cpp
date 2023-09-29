#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/continuous/NBodyPhaseSpaceDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using NBodyPhaseSpaceDistribution = block::NBodyPhaseSpaceDistribution;

std::vector< double > chunk();
void verifyChunk( const NBodyPhaseSpaceDistribution& );

SCENARIO( "NBodyPhaseSpaceDistribution" ) {

  GIVEN( "valid data for a NBodyPhaseSpaceDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double emin = 2.249999e-3;
      double emax = 20.;
      unsigned int npsx = 4;
      double ap = .9914722;
      unsigned int interpolation = 2;

      std::vector< double > values = { 0., 0.25, 0.75, 1. };
      std::vector< double > pdf = { 1., 1., 1., 1. };
      std::vector< double > cdf = { 0., 0.33, 0.66, 1. };

      NBodyPhaseSpaceDistribution chunk( emin, emax, npsx, ap, interpolation,
                                         std::move( values ),
                                         std::move( pdf ),
                                         std::move( cdf ) );

      THEN( "a NBodyPhaseSpaceDistribution can be constructed and members can "
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

      NBodyPhaseSpaceDistribution chunk( xss.begin(), xss.end(),
                                         2.249999e-3, 20. );

      THEN( "a NBodyPhaseSpaceDistribution can be constructed and members can "
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

  return { 4.00000000000E+00,   9.91472200000E-01,
           2.00000000000E+00,   4.00000000000E+00,
           0.00000000000E+00,   2.50000000000E-01,   7.50000000000E-01,   1.00000000000E+00,
           1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,   1.00000000000E+00,
           0.00000000000E+00,   3.30000000000E-01,   6.60000000000E-01,   1.00000000000E+00  };
}

void verifyChunk( const NBodyPhaseSpaceDistribution& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 16 == chunk.length() );
  CHECK( "NBodyPhaseSpaceDistribution" == chunk.name() );

  CHECK( EnergyDistributionType::NBodyPhaseSpace == chunk.LAW() );
  CHECK( EnergyDistributionType::NBodyPhaseSpace == chunk.type() );

  CHECK( 2.249999e-3 == Approx( chunk.minimumIncidentEnergy() ) );
  CHECK( 20. == Approx( chunk.maximumIncidentEnergy() ) );

  CHECK( 4 == chunk.NPSX() );
  CHECK( 4 == chunk.numberParticles() );
  CHECK( .9914722 == Approx( chunk.AP() ) );
  CHECK( .9914722 == Approx( chunk.totalMassRatio() ) );
  CHECK( 2 == chunk.interpolation() );
  CHECK( 4 == chunk.numberValues() );

  CHECK( 0. == Approx( chunk.values()[0] ) );
  CHECK( .25 == Approx( chunk.values()[1] ) );
  CHECK( .75 == Approx( chunk.values()[2] ) );
  CHECK( 1. == Approx( chunk.values()[3] ) );
  CHECK( 1. == Approx( chunk.pdf()[0] ) );
  CHECK( 1. == Approx( chunk.pdf()[1] ) );
  CHECK( 1. == Approx( chunk.pdf()[2] ) );
  CHECK( 1. == Approx( chunk.pdf()[3] ) );
  CHECK( 0. == Approx( chunk.cdf()[0] ) );
  CHECK( .33 == Approx( chunk.cdf()[1] ) );
  CHECK( .66 == Approx( chunk.cdf()[2] ) );
  CHECK( 1. == Approx( chunk.cdf()[3] ) );
}
