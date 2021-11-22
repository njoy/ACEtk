#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/NBodyPhaseSpaceDistribution.hpp"

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

      NBodyPhaseSpaceDistribution chunk( emin, emax, npsx, ap );

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

  return { 4.00000000000E+00,   9.91472200000E-01 };
}

void verifyChunk( const NBodyPhaseSpaceDistribution& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.length() );
  CHECK( "DLW::NBodyPhaseSpaceDistribution" == chunk.name() );

  CHECK( EnergyDistributionType::NBodyPhaseSpace == chunk.LAW() );
  CHECK( EnergyDistributionType::NBodyPhaseSpace == chunk.type() );

  CHECK( 2.249999e-3 == Approx( chunk.minimumIncidentEnergy() ) );
  CHECK( 20. == Approx( chunk.maximumIncidentEnergy() ) );

  CHECK( 4 == chunk.NPSX() );
  CHECK( 4 == chunk.numberParticles() );
  CHECK( .9914722 == Approx( chunk.AP() ) );
  CHECK( .9914722 == Approx( chunk.totalMassRatio() ) );
}
