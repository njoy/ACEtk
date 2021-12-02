#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/TwoBodyTransferDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TwoBodyTransferDistribution = block::TwoBodyTransferDistribution;

std::vector< double > chunk();
void verifyChunk( const TwoBodyTransferDistribution& );

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

      TwoBodyTransferDistribution chunk( xss.begin(), xss.end(),
                                         2.249999e-3, 20. );

      THEN( "a TwoBodyTransferDistribution can be constructed and members can "
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

  return { 7.71295800000E-05,   9.91472200000E-01 };
}

void verifyChunk( const TwoBodyTransferDistribution& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.length() );
  CHECK( "TwoBodyTransferDistribution" == chunk.name() );

  CHECK( EnergyDistributionType::TwoBodyTransfer == chunk.LAW() );
  CHECK( EnergyDistributionType::TwoBodyTransfer == chunk.type() );

  CHECK( 2.249999e-3 == Approx( chunk.minimumIncidentEnergy() ) );
  CHECK( 20. == Approx( chunk.maximumIncidentEnergy() ) );

  CHECK( 7.71295800000E-05 == Approx( chunk.C1() ) );
  CHECK( .9914722 == Approx( chunk.C2() ) );
}
