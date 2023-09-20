#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/ElectronElasticAngularDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ElectronElasticAngularDistributionBlock = block::ElectronElasticAngularDistributionBlock;
using ElectronTabulatedAngularDistribution = block::ElectronTabulatedAngularDistribution;

std::vector< double > chunk();
void verifyChunk( const ElectronElasticAngularDistributionBlock& );

SCENARIO( "ElectronElasticAngularDistributionBlock" ) {

  GIVEN( "valid data for a ElectronElasticAngularDistributionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< ElectronTabulatedAngularDistribution > distributions = {

        ElectronTabulatedAngularDistribution( 1e-11, { -1.0, 1.0 }, { 0., 1. } ),
        ElectronTabulatedAngularDistribution(  1e-6, { -1.0, 0.0, 1.0 }, { 0., 0.75, 1. } ),
        ElectronTabulatedAngularDistribution(  1e-3, { -1.0, 0.5, 0.7, 1.0 }, { 0., 0.25, 0.5, 1. } ),
        ElectronTabulatedAngularDistribution(    1., { -1.0, 1.0 }, { 0., 1. } )
      };

      ElectronElasticAngularDistributionBlock chunk( std::move( distributions ) );

      THEN( "a ElectronElasticAngularDistributionBlock can be constructed and members can be tested" ) {

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

      ElectronElasticAngularDistributionBlock chunk( xss.begin(), xss.end(), 4 );

      THEN( "a ElectronElasticAngularDistributionBlock can be constructed and members can be tested" ) {

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

  // first value of the second xs increased by 1 for testing purposes
  return {

    1e-11, 1e-6, 1e-3, 1.,
        2,    3,    4,  2,
        0,    4,   10, 18,
     -1.0, 1.0, 0., 1.,
     -1.0, 0.0, 1.0, 0., 0.75, 1.,
     -1.0, 0.5, 0.7, 1.0, 0., 0.25, 0.5, 1.,
     -1.0, 1.0, 0., 1. };
}

void verifyChunk( const ElectronElasticAngularDistributionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 34 == chunk.length() );
  CHECK( "ELAS" == chunk.name() );

  CHECK( 4 == chunk.NA() );
  CHECK( 4 == chunk.numberEnergyPoints() );
  CHECK( 4 == chunk.energies().size() );
  CHECK( 4 == chunk.data().size() );

  CHECK(  1 == chunk.LAND(1) );
  CHECK(  5 == chunk.LAND(2) );
  CHECK( 11 == chunk.LAND(3) );
  CHECK( 19 == chunk.LAND(4) );
  CHECK(  1 == chunk.angularDistributionLocator(1) );
  CHECK(  5 == chunk.angularDistributionLocator(2) );
  CHECK( 11 == chunk.angularDistributionLocator(3) );
  CHECK( 19 == chunk.angularDistributionLocator(4) );

  auto distribution = chunk.angularDistribution(1);
  CHECK( 1e-11 == distribution.energy() );
  CHECK( 2 == distribution.numberCosines() );

  distribution = chunk.angularDistribution(2);
  CHECK( 1e-6 == distribution.energy() );
  CHECK( 3 == distribution.numberCosines() );

  distribution = chunk.angularDistribution(3);
  CHECK( 1e-3 == distribution.energy() );
  CHECK( 4 == distribution.numberCosines() );

  distribution = chunk.angularDistribution(4);
  CHECK( 1. == distribution.energy() );
  CHECK( 2 == distribution.numberCosines() );
}
