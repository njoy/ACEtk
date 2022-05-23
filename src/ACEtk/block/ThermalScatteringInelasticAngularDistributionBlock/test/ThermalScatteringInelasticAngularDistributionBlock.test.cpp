#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/ThermalScatteringInelasticAngularDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ThermalScatteringInelasticAngularDistributionBlock = block::ThermalScatteringInelasticAngularDistributionBlock;
using ThermalScatteringDiscreteCosines = block::ThermalScatteringDiscreteCosines;
using ThermalScatteringDiscreteCosinesWithProbability = block::ThermalScatteringDiscreteCosinesWithProbability;

std::vector< double > chunk();
void verifyChunk( const ThermalScatteringInelasticAngularDistributionBlock& );

SCENARIO( "ThermalScatteringInelasticAngularDistributionBlock" ) {

  GIVEN( "valid data for a ThermalScatteringInelasticAngularDistributionBlock "
         "instance using IFENG = 1" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      bool skewed = true;
      std::vector< std::vector< ThermalScatteringDiscreteCosines > > cosines = {

        { { 1., { -1.0, -0.9, 1.0 } },
          { 2., { -1.0, 0.0, 1.0 } } },
        { { 3., { -1.0, 0.5, 1.0 } },
          { 4., { -1.0, 0.9, 1.0 } } },
        { { 5., { -1.0, 0.4, 1.0 } },
          { 6., { -1.0, 0.8, 1.0 } } },
        { { 7., { -1.0, 0.3, 1.0 } },
          { 8., { -1.0, 0.7, 1.0 } } }
      };

      ThermalScatteringInelasticAngularDistributionBlock
      chunk( std::move( cosines ), skewed );

      THEN( "a ThermalScatteringInelasticAngularDistributionBlock can be constructed "
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

      ThermalScatteringInelasticAngularDistributionBlock
      chunk( 1, 2, 3, 4, xss.begin(), xss.end() );

      THEN( "a ThermalScatteringInelasticAngularDistributionBlock can be constructed "
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

     1.00000000000E+00, -1.00000000000E+00, -0.90000000000E+00,  1.00000000000E+00,
     2.00000000000E+00, -1.00000000000E+00,  0.00000000000E+00,  1.00000000000E+00,
     3.00000000000E+00, -1.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00,
     4.00000000000E+00, -1.00000000000E+00,  0.90000000000E+00,  1.00000000000E+00,
     5.00000000000E+00, -1.00000000000E+00,  0.40000000000E+00,  1.00000000000E+00,
     6.00000000000E+00, -1.00000000000E+00,  0.80000000000E+00,  1.00000000000E+00,
     7.00000000000E+00, -1.00000000000E+00,  0.30000000000E+00,  1.00000000000E+00,
     8.00000000000E+00, -1.00000000000E+00,  0.70000000000E+00,  1.00000000000E+00
  };
}

void verifyChunk( const ThermalScatteringInelasticAngularDistributionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 32 == chunk.length() );
  CHECK( "ThermalScatteringInelasticAngularDistributionBlock" == chunk.name() );

  CHECK( 1 == chunk.IFENG() );
  CHECK( 1 == chunk.secondaryEnergyMode() );
  CHECK( 4 == chunk.NE() );
  CHECK( 4 == chunk.numberIncidentEnergies() );
  CHECK( 3 == chunk.NC() );
  CHECK( 3 == chunk.numberDiscreteCosines() );
  CHECK( 2 == chunk.NIEB() );
  CHECK( 2 == chunk.numberOutgoingEnergies() );

  auto data11 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 1, 1 ) );
  CHECK( 3 == data11.NC() );
  CHECK( -1. == Approx( data11.cosines()[0] ) );
  CHECK( -.9 == Approx( data11.cosines()[1] ) );
  CHECK( +1. == Approx( data11.cosines()[2] ) );

  auto data12 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 1, 2 ) );
  CHECK( 3 == data12.NC() );
  CHECK( -1. == Approx( data12.cosines()[0] ) );
  CHECK(  0. == Approx( data12.cosines()[1] ) );
  CHECK( +1. == Approx( data12.cosines()[2] ) );

  auto data21 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 2, 1 ) );
  CHECK( 3 == data21.NC() );
  CHECK( -1. == Approx( data21.cosines()[0] ) );
  CHECK(  .5 == Approx( data21.cosines()[1] ) );
  CHECK( +1. == Approx( data21.cosines()[2] ) );

  auto data22 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 2, 2 ) );
  CHECK( 3 == data22.NC() );
  CHECK( -1. == Approx( data22.cosines()[0] ) );
  CHECK(  .9 == Approx( data22.cosines()[1] ) );
  CHECK( +1. == Approx( data22.cosines()[2] ) );

  auto data31 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 3, 1 ) );
  CHECK( 3 == data31.NC() );
  CHECK( -1. == Approx( data31.cosines()[0] ) );
  CHECK(  .4 == Approx( data31.cosines()[1] ) );
  CHECK( +1. == Approx( data31.cosines()[2] ) );

  auto data32 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 3, 2 ) );
  CHECK( 3 == data32.NC() );
  CHECK( -1. == Approx( data32.cosines()[0] ) );
  CHECK(  .8 == Approx( data32.cosines()[1] ) );
  CHECK( +1. == Approx( data32.cosines()[2] ) );

  auto data41 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 4, 1 ) );
  CHECK( 3 == data41.NC() );
  CHECK( -1. == Approx( data41.cosines()[0] ) );
  CHECK(  .3 == Approx( data41.cosines()[1] ) );
  CHECK( +1. == Approx( data41.cosines()[2] ) );

  auto data42 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 4, 2 ) );
  CHECK( 3 == data42.NC() );
  CHECK( -1. == Approx( data42.cosines()[0] ) );
  CHECK(  .7 == Approx( data42.cosines()[1] ) );
  CHECK( +1. == Approx( data42.cosines()[2] ) );
}
