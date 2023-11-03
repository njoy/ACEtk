#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/continuous/DiscretePhotonDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using DiscretePhotonDistribution = continuous::DiscretePhotonDistribution;

std::vector< double > chunk();
void verifyChunk( const DiscretePhotonDistribution& );

SCENARIO( "DiscretePhotonDistribution" ) {

  GIVEN( "valid data for a DiscretePhotonDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double emin = 1e-5;
      double emax = 20.;
      unsigned int lp = 2;
      double energy = 1e+5;

      DiscretePhotonDistribution chunk( emin, emax, lp, energy );

      THEN( "a DiscretePhotonDistribution can be constructed and members can "
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

      DiscretePhotonDistribution chunk( xss.begin(), xss.end(),
                                        1e-5, 20. );

      THEN( "a DiscretePhotonDistribution can be constructed and members can "
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

  return { 2.0, 1e+5 };
}

void verifyChunk( const DiscretePhotonDistribution& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.length() );
  CHECK( "DiscretePhotonDistribution" == chunk.name() );

  CHECK( EnergyDistributionType::DiscretePhoton == chunk.LAW() );
  CHECK( EnergyDistributionType::DiscretePhoton == chunk.type() );

  CHECK( 1e-5 == Approx( chunk.minimumIncidentEnergy() ) );
  CHECK( 20. == Approx( chunk.maximumIncidentEnergy() ) );

  CHECK( 2 == Approx( chunk.LP() ) );
  CHECK( 2 == Approx( chunk.primaryPhotonFlag() ) );
  CHECK( true == Approx( chunk.isPrimaryPhoton() ) );
  CHECK( 1e+5 == Approx( chunk.EG() ) );
  CHECK( 1e+5 == Approx( chunk.photonOrBindingEnergy() ) );
}
