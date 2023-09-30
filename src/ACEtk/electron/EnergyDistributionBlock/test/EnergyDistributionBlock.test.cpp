// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/EnergyDistributionBlock.hpp"

// other includes
#include "ACEtk/fromFile.hpp"

// convenience typedefs
using namespace njoy::ACEtk;
using EnergyDistributionBlock = electron::EnergyDistributionBlock;
using TabulatedEnergyDistribution = electron::TabulatedEnergyDistribution;

std::vector< double > chunk();
void verifyChunk( const EnergyDistributionBlock& );

SCENARIO( "EnergyDistributionBlock" ) {

  GIVEN( "valid data for a EnergyDistributionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< TabulatedEnergyDistribution > distributions = {

        TabulatedEnergyDistribution( 1e-11, { 1e-12, 9e-12 }, { 0., 1. } ),
        TabulatedEnergyDistribution(  1e-6, { 1e-11, 1e-9, 9e-7 }, { 0., 0.75, 1. } ),
        TabulatedEnergyDistribution(  1e-3, { 1e-11, 1e-6, 1e-4, 9e-4 }, { 0., 0.25, 0.5, 1. } ),
        TabulatedEnergyDistribution(    1., { 1e-11, 0.999 }, { 0., 1. } )
      };

      EnergyDistributionBlock chunk( std::move( distributions ) );

      THEN( "a EnergyDistributionBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      EnergyDistributionBlock chunk( xss.begin(), xss.end(), 4 );

      THEN( "a EnergyDistributionBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  // first value of the second xs increased by 1 for testing purposes
  return {

    1e-11, 1e-6, 1e-3, 1.,
        2,    3,    4,  2,
        0,    4,   10, 18,
    1e-12, 9e-12, 0., 1.,
    1e-11, 1e-9, 9e-7, 0., 0.75, 1.,
    1e-11, 1e-6, 1e-4, 9e-4, 0., 0.25, 0.5, 1.,
    1e-11, 0.999, 0., 1. };
}

void verifyChunk( const EnergyDistributionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 34 == chunk.length() );
  CHECK( "BREME" == chunk.name() );

  CHECK( 4 == chunk.NB() );
  CHECK( 4 == chunk.numberEnergyPoints() );
  CHECK( 4 == chunk.energies().size() );
  CHECK( 4 == chunk.distributions().size() );

  CHECK(  1 == chunk.LLOC(1) );
  CHECK(  5 == chunk.LLOC(2) );
  CHECK( 11 == chunk.LLOC(3) );
  CHECK( 19 == chunk.LLOC(4) );
  CHECK(  1 == chunk.distributionLocator(1) );
  CHECK(  5 == chunk.distributionLocator(2) );
  CHECK( 11 == chunk.distributionLocator(3) );
  CHECK( 19 == chunk.distributionLocator(4) );

  auto distribution = chunk.distribution(1);
  CHECK( 1e-11 == distribution.energy() );
  CHECK( 2 == distribution.numberOutgoingEnergies() );

  distribution = chunk.distribution(2);
  CHECK( 1e-6 == distribution.energy() );
  CHECK( 3 == distribution.numberOutgoingEnergies() );

  distribution = chunk.distribution(3);
  CHECK( 1e-3 == distribution.energy() );
  CHECK( 4 == distribution.numberOutgoingEnergies() );

  distribution = chunk.distribution(4);
  CHECK( 1. == distribution.energy() );
  CHECK( 2 == distribution.numberOutgoingEnergies() );
}
