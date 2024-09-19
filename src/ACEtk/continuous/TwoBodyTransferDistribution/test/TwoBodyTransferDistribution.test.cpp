// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/TwoBodyTransferDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TwoBodyTransferDistribution = continuous::TwoBodyTransferDistribution;

std::vector< double > chunk();
void verifyChunk( const TwoBodyTransferDistribution&, const std::vector< double >& );
TwoBodyTransferDistribution makeDummyBlock();

SCENARIO( "TwoBodyTransferDistribution" ) {

  GIVEN( "valid data for a TwoBodyTransferDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double emin = 2.249999e-3;
      double emax = 20.;
      double c1 = 7.712958e-05;
      double c2 = .9914722;

      TwoBodyTransferDistribution chunk( emin, emax, c1, c2 );

      THEN( "a TwoBodyTransferDistribution can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      TwoBodyTransferDistribution chunk( xss.begin(), xss.end(),
                                         2.249999e-3, 20. );

      THEN( "a TwoBodyTransferDistribution can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 7.71295800000E-05,   9.91472200000E-01 };
}

void verifyChunk( const TwoBodyTransferDistribution& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.length() );
  CHECK( "TwoBodyTransferDistribution" == chunk.name() );

  CHECK( EnergyDistributionType::TwoBodyTransfer == chunk.LAW() );
  CHECK( EnergyDistributionType::TwoBodyTransfer == chunk.type() );

  CHECK_THAT( 2.249999e-3, WithinRel( chunk.minimumIncidentEnergy() ) );
  CHECK_THAT( 20., WithinRel( chunk.maximumIncidentEnergy() ) );

  CHECK_THAT( 7.71295800000E-05, WithinRel( chunk.C1() ) );
  CHECK_THAT( .9914722, WithinRel( chunk.C2() ) );
}
