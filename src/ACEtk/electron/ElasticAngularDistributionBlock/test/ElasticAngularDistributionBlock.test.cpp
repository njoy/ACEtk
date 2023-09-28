#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/electron/ElasticAngularDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ElasticAngularDistributionBlock = electron::ElasticAngularDistributionBlock;
using TabulatedAngularDistribution = electron::TabulatedAngularDistribution;

std::vector< double > chunk();
void verifyChunk( const ElasticAngularDistributionBlock& );

SCENARIO( "ElasticAngularDistributionBlock" ) {

  GIVEN( "valid data for a ElasticAngularDistributionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< TabulatedAngularDistribution > distributions = {

        TabulatedAngularDistribution( 1e-11, { -1.0, 1.0 }, { 0., 1. } ),
        TabulatedAngularDistribution(  1e-6, { -1.0, 0.0, 1.0 }, { 0., 0.75, 1. } ),
        TabulatedAngularDistribution(  1e-3, { -1.0, 0.5, 0.7, 1.0 }, { 0., 0.25, 0.5, 1. } ),
        TabulatedAngularDistribution(    1., { -1.0, 1.0 }, { 0., 1. } )
      };

      ElasticAngularDistributionBlock chunk( std::move( distributions ) );

      THEN( "a ElasticAngularDistributionBlock can be constructed and members can be tested" ) {

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

      ElasticAngularDistributionBlock chunk( xss.begin(), xss.end(), 4 );

      THEN( "a ElasticAngularDistributionBlock can be constructed and members can be tested" ) {

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

void verifyChunk( const ElasticAngularDistributionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 34 == chunk.length() );
  CHECK( "ELAS" == chunk.name() );

  CHECK( 4 == chunk.NA() );
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
  CHECK( 2 == distribution.numberCosines() );

  distribution = chunk.distribution(2);
  CHECK( 1e-6 == distribution.energy() );
  CHECK( 3 == distribution.numberCosines() );

  distribution = chunk.distribution(3);
  CHECK( 1e-3 == distribution.energy() );
  CHECK( 4 == distribution.numberCosines() );

  distribution = chunk.distribution(4);
  CHECK( 1. == distribution.energy() );
  CHECK( 2 == distribution.numberCosines() );
}
