// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/thermal/ElasticAngularDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ElasticAngularDistributionBlock = thermal::ElasticAngularDistributionBlock;

std::vector< double > chunk();
void verifyChunk( const ElasticAngularDistributionBlock&, const std::vector< double >& );
ElasticAngularDistributionBlock makeDummyBlock();

SCENARIO( "ElasticAngularDistributionBlock" ) {

  GIVEN( "valid data for a ElasticAngularDistributionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< std::vector< double > > cosines = {

        { -1.0, -0.9, 1.0 }, { -1.0, 0.0, 1.0 }, { -1.0, 0.5, 1.0 },
        { -1.0, 0.9, 1.0 }
      };

      ElasticAngularDistributionBlock chunk( std::move( cosines ) );

      THEN( "a ElasticAngularDistributionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      ElasticAngularDistributionBlock chunk( xss.begin(), xss.end(),
                                                              4, 3 );

      THEN( "a ElasticAngularDistributionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

    -1.00000000000E+00, -0.90000000000E+00,  1.00000000000E+00,
    -1.00000000000E+00,  0.00000000000E+00,  1.00000000000E+00,
    -1.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00,
    -1.00000000000E+00,  0.90000000000E+00,  1.00000000000E+00
  };
}

void verifyChunk( const ElasticAngularDistributionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 12 == chunk.length() );
  CHECK( "ElasticAngularDistributionBlock" == chunk.name() );

  CHECK( 4 == chunk.NE() );
  CHECK( 4 == chunk.numberIncidentEnergies() );
  CHECK( 3 == chunk.NC() );
  CHECK( 3 == chunk.numberDiscreteCosines() );
  CHECK( 2 == chunk.NCL() );
  CHECK( 2 == chunk.elasticDimensioningParameter() );

  auto cosines = chunk.cosines( 1 );
  CHECK( 3 == cosines.size() );
  CHECK_THAT( -1., WithinRel( cosines[0] ) );
  CHECK_THAT( -.9, WithinRel( cosines[1] ) );
  CHECK_THAT( +1., WithinRel( cosines[2] ) );

  cosines = chunk.cosines( 2 );
  CHECK( 3 == cosines.size() );
  CHECK_THAT( -1., WithinRel( cosines[0] ) );
  CHECK_THAT(  0., WithinRel( cosines[1] ) );
  CHECK_THAT( +1., WithinRel( cosines[2] ) );

  cosines = chunk.cosines( 3 );
  CHECK( 3 == cosines.size() );
  CHECK_THAT( -1., WithinRel( cosines[0] ) );
  CHECK_THAT(  .5, WithinRel( cosines[1] ) );
  CHECK_THAT( +1., WithinRel( cosines[2] ) );

  cosines = chunk.cosines( 4 );
  CHECK( 3 == cosines.size() );
  CHECK_THAT( -1., WithinRel( cosines[0] ) );
  CHECK_THAT(  .9, WithinRel( cosines[1] ) );
  CHECK_THAT( +1., WithinRel( cosines[2] ) );
}
