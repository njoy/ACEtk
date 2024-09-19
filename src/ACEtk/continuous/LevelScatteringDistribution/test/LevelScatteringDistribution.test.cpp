// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/LevelScatteringDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using LevelScatteringDistribution = continuous::LevelScatteringDistribution;

std::vector< double > chunk();
void verifyChunk( const LevelScatteringDistribution&, const std::vector< double >& );
LevelScatteringDistribution makeDummyBlock();

SCENARIO( "LevelScatteringDistribution" ) {

  GIVEN( "valid data for a LevelScatteringDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double emin = 2.249999e-3;
      double emax = 20.;
      double c1 = 7.712958e-05;
      double c2 = .9914722;

      LevelScatteringDistribution chunk( emin, emax, c1, c2 );

      THEN( "a LevelScatteringDistribution can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      LevelScatteringDistribution chunk( xss.begin(), xss.end(),
                                         2.249999e-3, 20. );

      THEN( "a LevelScatteringDistribution can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 7.71295800000E-05,   9.91472200000E-01 };
}

void verifyChunk( const LevelScatteringDistribution& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.length() );
  CHECK( "LevelScatteringDistribution" == chunk.name() );

  CHECK( EnergyDistributionType::LevelScattering == chunk.LAW() );
  CHECK( EnergyDistributionType::LevelScattering == chunk.type() );

  CHECK_THAT( 2.249999e-3, WithinRel( chunk.minimumIncidentEnergy() ) );
  CHECK_THAT( 20., WithinRel( chunk.maximumIncidentEnergy() ) );

  CHECK_THAT( 7.71295800000E-05, WithinRel( chunk.C1() ) );
  CHECK_THAT( .9914722, WithinRel( chunk.C2() ) );
}
