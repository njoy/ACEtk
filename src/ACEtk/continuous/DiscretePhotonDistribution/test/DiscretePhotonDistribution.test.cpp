// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/DiscretePhotonDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using DiscretePhotonDistribution = continuous::DiscretePhotonDistribution;

std::vector< double > chunk();
void verifyChunk( const DiscretePhotonDistribution&, const std::vector< double >& );
DiscretePhotonDistribution makeDummyBlock();

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

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      DiscretePhotonDistribution chunk( xss.begin(), xss.end(),
                                        1e-5, 20. );

      THEN( "a DiscretePhotonDistribution can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 2.0, 1e+5 };
}

void verifyChunk( const DiscretePhotonDistribution& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.length() );
  CHECK( "DiscretePhotonDistribution" == chunk.name() );

  CHECK( EnergyDistributionType::DiscretePhoton == chunk.LAW() );
  CHECK( EnergyDistributionType::DiscretePhoton == chunk.type() );

  CHECK_THAT( 1e-5, WithinRel( chunk.minimumIncidentEnergy() ) );
  CHECK_THAT( 20., WithinRel( chunk.maximumIncidentEnergy() ) );

  CHECK( 2 == chunk.LP() );
  CHECK( 2 == chunk.primaryPhotonFlag() );
  CHECK( true == chunk.isPrimaryPhoton() );
  CHECK_THAT( 1e+5, WithinRel( chunk.EG() ) );
  CHECK_THAT( 1e+5, WithinRel( chunk.photonOrBindingEnergy() ) );
}
