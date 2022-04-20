#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/ThermalScatteringElasticAngularDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ThermalScatteringElasticAngularDistributionBlock = block::ThermalScatteringElasticAngularDistributionBlock;

std::vector< double > chunk();
void verifyChunk( const ThermalScatteringElasticAngularDistributionBlock& );

SCENARIO( "ThermalScatteringElasticAngularDistributionBlock" ) {

  GIVEN( "valid data for a ThermalScatteringElasticAngularDistributionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< std::vector< double > > cosines = {

        { -1.0, -0.9, 1.0 }, { -1.0, 0.0, 1.0 }, { -1.0, 0.5, 1.0 },
        { -1.0, 0.9, 1.0 }
      };

      ThermalScatteringElasticAngularDistributionBlock chunk( std::move( cosines ) );

      THEN( "a ThermalScatteringElasticAngularDistributionBlock can be constructed "
            "and members can be tested" ) {

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

      ThermalScatteringElasticAngularDistributionBlock chunk( 4, 3,
                                                              xss.begin(), xss.end() );

      THEN( "a ThermalScatteringElasticAngularDistributionBlock can be constructed "
            "and members can be tested" ) {

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

  return {

    -1.00000000000E+00, -0.90000000000E+00,  1.00000000000E+00,
    -1.00000000000E+00,  0.00000000000E+00,  1.00000000000E+00,
    -1.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00,
    -1.00000000000E+00,  0.90000000000E+00,  1.00000000000E+00,
  };
}

void verifyChunk( const ThermalScatteringElasticAngularDistributionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 12 == chunk.length() );
  CHECK( "ThermalScatteringElasticAngularDistributionBlock" == chunk.name() );

  CHECK( 4 == chunk.NE() );
  CHECK( 4 == chunk.numberEnergies() );
  CHECK( 3 == chunk.NC() );
  CHECK( 3 == chunk.numberDiscreteCosines() );

  auto cosines = chunk.cosines( 1 );
  CHECK( 3 == cosines.size() );
  CHECK( -1. == Approx( cosines[0] ) );
  CHECK( -.9 == Approx( cosines[1] ) );
  CHECK( +1. == Approx( cosines[2] ) );

  cosines = chunk.cosines( 2 );
  CHECK( 3 == cosines.size() );
  CHECK( -1. == Approx( cosines[0] ) );
  CHECK(  0. == Approx( cosines[1] ) );
  CHECK( +1. == Approx( cosines[2] ) );

  cosines = chunk.cosines( 3 );
  CHECK( 3 == cosines.size() );
  CHECK( -1. == Approx( cosines[0] ) );
  CHECK(  .5 == Approx( cosines[1] ) );
  CHECK( +1. == Approx( cosines[2] ) );

  cosines = chunk.cosines( 4 );
  CHECK( 3 == cosines.size() );
  CHECK( -1. == Approx( cosines[0] ) );
  CHECK(  .9 == Approx( cosines[1] ) );
  CHECK( +1. == Approx( cosines[2] ) );
}
