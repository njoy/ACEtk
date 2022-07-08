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
std::vector< double > chunkWithIFENG2();
void verifyChunk( const ThermalScatteringInelasticAngularDistributionBlock& );
void verifyChunkWithIFENG2( const ThermalScatteringInelasticAngularDistributionBlock& );

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
      chunk( 1, 2, 3, 4, 9, xss.begin(), xss.end() );

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

  GIVEN( "valid data for a ThermalScatteringInelasticAngularDistributionBlock "
         "instance using IFENG = 2" ) {

    std::vector< double > xss = chunkWithIFENG2();

    WHEN( "the data is given explicitly" ) {

      std::vector< std::vector< ThermalScatteringDiscreteCosinesWithProbability > > cosines = {

        { {  1., 0.5, 0., { -1.0, -0.9, 1.0 } },
          {  2., 0.5, 1., { -1.0, 0.0, 1.0 } } },
        { {  3., 0.25, 0.00, { -1.0, 0.5, 1.0 } },
          {  4., 0.25, 0.33, { -1.0, 0.9, 1.0 } },
          {  5., 0.25, 0.66, { -1.0, 0.4, 1.0 } },
          {  6., 0.25, 1.00, { -1.0, 0.8, 1.0 } } },
        { {  7., 0.33, 0.0, { -1.0, 0.3, 1.0 } },
          {  8., 0.33, 0.5, { -1.0, 0.7, 1.0 } },
          {  9., 0.33, 1.0, { -1.0, 0.6, 1.0 } } },
        { { 10., 0.33, 0.0, { -1.0, 0.2, 1.0 } },
          { 11., 0.33, 0.5, { -1.0, 0.5, 1.0 } },
          { 12., 0.33, 1.0, { -1.0, 0.4, 1.0 } } }
      };

      ThermalScatteringInelasticAngularDistributionBlock
      chunk( std::move( cosines ), 9 );

      THEN( "a ThermalScatteringInelasticAngularDistributionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunkWithIFENG2( chunk );
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
      chunk( 2, 0, 3, 4, 9, xss.begin(), xss.end() );

      THEN( "a ThermalScatteringInelasticAngularDistributionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunkWithIFENG2( chunk );
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

std::vector< double > chunkWithIFENG2() {

  return {

                    17,                 29,                 53,                 71,
                     2,                  4,                  3,                  3,
     1.00000000000E+00,  5.00000000000E-01,  0.00000000000E+00, -1.00000000000E+00, -0.90000000000E+00,  1.00000000000E+00,
     2.00000000000E+00,  5.00000000000E-01,  1.00000000000E+00, -1.00000000000E+00,  0.00000000000E+00,  1.00000000000E+00,
     3.00000000000E+00,  2.50000000000E-01,  0.00000000000E+00, -1.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00,
     4.00000000000E+00,  2.50000000000E-01,  3.30000000000E-01, -1.00000000000E+00,  0.90000000000E+00,  1.00000000000E+00,
     5.00000000000E+00,  2.50000000000E-01,  6.60000000000E-01, -1.00000000000E+00,  0.40000000000E+00,  1.00000000000E+00,
     6.00000000000E+00,  2.50000000000E-01,  1.00000000000E+00, -1.00000000000E+00,  0.80000000000E+00,  1.00000000000E+00,
     7.00000000000E+00,  3.30000000000E-01,  0.00000000000E+00, -1.00000000000E+00,  0.30000000000E+00,  1.00000000000E+00,
     8.00000000000E+00,  3.30000000000E-01,  5.00000000000E-01, -1.00000000000E+00,  0.70000000000E+00,  1.00000000000E+00,
     9.00000000000E+00,  3.30000000000E-01,  1.00000000000E+00, -1.00000000000E+00,  0.60000000000E+00,  1.00000000000E+00,
    10.00000000000E+00,  3.30000000000E-01,  0.00000000000E+00, -1.00000000000E+00,  0.20000000000E+00,  1.00000000000E+00,
    11.00000000000E+00,  3.30000000000E-01,  5.00000000000E-01, -1.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00,
    12.00000000000E+00,  3.30000000000E-01,  1.00000000000E+00, -1.00000000000E+00,  0.40000000000E+00,  1.00000000000E+00
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
  CHECK( 2 == chunk.NIL() );
  CHECK( 2 == chunk.inelasticDimensioningParameter() );

  CHECK( 2 == chunk.NIEB( 1 ) );
  CHECK( 2 == chunk.NIEB( 2 ) );
  CHECK( 2 == chunk.NIEB( 3 ) );
  CHECK( 2 == chunk.NIEB( 4 ) );
  CHECK( 2 == chunk.numberOutgoingEnergies( 1 ) );
  CHECK( 2 == chunk.numberOutgoingEnergies( 2 ) );
  CHECK( 2 == chunk.numberOutgoingEnergies( 3 ) );
  CHECK( 2 == chunk.numberOutgoingEnergies( 4 ) );

  auto data11 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 1, 1 ) );
  CHECK( 3 == data11.NC() );
  CHECK( 3 == data11.numberDiscreteCosines() );
  CHECK( 1. == Approx( data11.energy() ) );
  CHECK( -1. == Approx( data11.cosines()[0] ) );
  CHECK( -.9 == Approx( data11.cosines()[1] ) );
  CHECK( +1. == Approx( data11.cosines()[2] ) );

  auto data12 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 1, 2 ) );
  CHECK( 3 == data12.NC() );
  CHECK( 3 == data12.numberDiscreteCosines() );
  CHECK( 2. == Approx( data12.energy() ) );
  CHECK( -1. == Approx( data12.cosines()[0] ) );
  CHECK(  0. == Approx( data12.cosines()[1] ) );
  CHECK( +1. == Approx( data12.cosines()[2] ) );

  auto data21 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 2, 1 ) );
  CHECK( 3 == data21.NC() );
  CHECK( 3 == data21.numberDiscreteCosines() );
  CHECK( 3. == Approx( data21.energy() ) );
  CHECK( -1. == Approx( data21.cosines()[0] ) );
  CHECK(  .5 == Approx( data21.cosines()[1] ) );
  CHECK( +1. == Approx( data21.cosines()[2] ) );

  auto data22 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 2, 2 ) );
  CHECK( 3 == data22.NC() );
  CHECK( 3 == data22.numberDiscreteCosines() );
  CHECK( 4. == Approx( data22.energy() ) );
  CHECK( -1. == Approx( data22.cosines()[0] ) );
  CHECK(  .9 == Approx( data22.cosines()[1] ) );
  CHECK( +1. == Approx( data22.cosines()[2] ) );

  auto data31 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 3, 1 ) );
  CHECK( 3 == data31.NC() );
  CHECK( 3 == data31.numberDiscreteCosines() );
  CHECK( 5. == Approx( data31.energy() ) );
  CHECK( -1. == Approx( data31.cosines()[0] ) );
  CHECK(  .4 == Approx( data31.cosines()[1] ) );
  CHECK( +1. == Approx( data31.cosines()[2] ) );

  auto data32 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 3, 2 ) );
  CHECK( 3 == data32.NC() );
  CHECK( 3 == data32.numberDiscreteCosines() );
  CHECK( 6. == Approx( data32.energy() ) );
  CHECK( -1. == Approx( data32.cosines()[0] ) );
  CHECK(  .8 == Approx( data32.cosines()[1] ) );
  CHECK( +1. == Approx( data32.cosines()[2] ) );

  auto data41 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 4, 1 ) );
  CHECK( 3 == data41.NC() );
  CHECK( 3 == data41.numberDiscreteCosines() );
  CHECK( 7. == Approx( data41.energy() ) );
  CHECK( -1. == Approx( data41.cosines()[0] ) );
  CHECK(  .3 == Approx( data41.cosines()[1] ) );
  CHECK( +1. == Approx( data41.cosines()[2] ) );

  auto data42 = std::get< ThermalScatteringDiscreteCosines >( chunk.discreteCosineData( 4, 2 ) );
  CHECK( 3 == data42.NC() );
  CHECK( 3 == data42.numberDiscreteCosines() );
  CHECK( 8. == Approx( data42.energy() ) );
  CHECK( -1. == Approx( data42.cosines()[0] ) );
  CHECK(  .7 == Approx( data42.cosines()[1] ) );
  CHECK( +1. == Approx( data42.cosines()[2] ) );
}

void verifyChunkWithIFENG2( const ThermalScatteringInelasticAngularDistributionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 80 == chunk.length() );
  CHECK( "ThermalScatteringInelasticAngularDistributionBlock" == chunk.name() );

  CHECK( 2 == chunk.IFENG() );
  CHECK( 2 == chunk.secondaryEnergyMode() );
  CHECK( 4 == chunk.NE() );
  CHECK( 4 == chunk.numberIncidentEnergies() );
  CHECK( 3 == chunk.NC() );
  CHECK( 3 == chunk.numberDiscreteCosines() );
  CHECK( 4 == chunk.NIL() );
  CHECK( 4 == chunk.inelasticDimensioningParameter() );

  CHECK( 2 == chunk.NIEB( 1 ) );
  CHECK( 4 == chunk.NIEB( 2 ) );
  CHECK( 3 == chunk.NIEB( 3 ) );
  CHECK( 3 == chunk.NIEB( 4 ) );
  CHECK( 2 == chunk.numberOutgoingEnergies( 1 ) );
  CHECK( 4 == chunk.numberOutgoingEnergies( 2 ) );
  CHECK( 3 == chunk.numberOutgoingEnergies( 3 ) );
  CHECK( 3 == chunk.numberOutgoingEnergies( 4 ) );

  auto data11 = std::get< ThermalScatteringDiscreteCosinesWithProbability >( chunk.discreteCosineData( 1, 1 ) );
  CHECK( 3 == data11.NC() );
  CHECK( 3 == data11.numberDiscreteCosines() );
  CHECK(  1. == Approx( data11.energy() ) );
  CHECK(  .5 == Approx( data11.pdf() ) );
  CHECK(  .0 == Approx( data11.cdf() ) );
  CHECK( -1. == Approx( data11.cosines()[0] ) );
  CHECK( -.9 == Approx( data11.cosines()[1] ) );
  CHECK( +1. == Approx( data11.cosines()[2] ) );

  auto data12 = std::get< ThermalScatteringDiscreteCosinesWithProbability >( chunk.discreteCosineData( 1, 2 ) );
  CHECK( 3 == data12.NC() );
  CHECK( 3 == data12.numberDiscreteCosines() );
  CHECK(  2. == Approx( data12.energy() ) );
  CHECK(  .5 == Approx( data12.pdf() ) );
  CHECK(  1. == Approx( data12.cdf() ) );
  CHECK( -1. == Approx( data12.cosines()[0] ) );
  CHECK(  0. == Approx( data12.cosines()[1] ) );
  CHECK( +1. == Approx( data12.cosines()[2] ) );

  auto data21 = std::get< ThermalScatteringDiscreteCosinesWithProbability >( chunk.discreteCosineData( 2, 1 ) );
  CHECK( 3 == data21.NC() );
  CHECK( 3 == data21.numberDiscreteCosines() );
  CHECK(  3. == Approx( data21.energy() ) );
  CHECK(  .25 == Approx( data21.pdf() ) );
  CHECK(  0. == Approx( data21.cdf() ) );
  CHECK( -1. == Approx( data21.cosines()[0] ) );
  CHECK(  .5 == Approx( data21.cosines()[1] ) );
  CHECK( +1. == Approx( data21.cosines()[2] ) );

  auto data22 = std::get< ThermalScatteringDiscreteCosinesWithProbability >( chunk.discreteCosineData( 2, 2 ) );
  CHECK( 3 == data22.NC() );
  CHECK( 3 == data22.numberDiscreteCosines() );
  CHECK(  4. == Approx( data22.energy() ) );
  CHECK(  .25 == Approx( data22.pdf() ) );
  CHECK(  0.33 == Approx( data22.cdf() ) );
  CHECK( -1. == Approx( data22.cosines()[0] ) );
  CHECK(  .9 == Approx( data22.cosines()[1] ) );
  CHECK( +1. == Approx( data22.cosines()[2] ) );

  auto data23 = std::get< ThermalScatteringDiscreteCosinesWithProbability >( chunk.discreteCosineData( 2, 3 ) );
  CHECK( 3 == data23.NC() );
  CHECK( 3 == data23.numberDiscreteCosines() );
  CHECK(  5. == Approx( data23.energy() ) );
  CHECK(  .25 == Approx( data23.pdf() ) );
  CHECK(  0.66 == Approx( data23.cdf() ) );
  CHECK( -1. == Approx( data23.cosines()[0] ) );
  CHECK(  .4 == Approx( data23.cosines()[1] ) );
  CHECK( +1. == Approx( data23.cosines()[2] ) );

  auto data24 = std::get< ThermalScatteringDiscreteCosinesWithProbability >( chunk.discreteCosineData( 2, 4 ) );
  CHECK( 3 == data24.NC() );
  CHECK( 3 == data24.numberDiscreteCosines() );
  CHECK(  6. == Approx( data24.energy() ) );
  CHECK(  .25 == Approx( data24.pdf() ) );
  CHECK(  1. == Approx( data24.cdf() ) );
  CHECK( -1. == Approx( data24.cosines()[0] ) );
  CHECK(  .8 == Approx( data24.cosines()[1] ) );
  CHECK( +1. == Approx( data24.cosines()[2] ) );

  auto data31 = std::get< ThermalScatteringDiscreteCosinesWithProbability >( chunk.discreteCosineData( 3, 1 ) );
  CHECK( 3 == data31.NC() );
  CHECK( 3 == data31.numberDiscreteCosines() );
  CHECK(  7. == Approx( data31.energy() ) );
  CHECK(  .33 == Approx( data31.pdf() ) );
  CHECK(  0. == Approx( data31.cdf() ) );
  CHECK( -1. == Approx( data31.cosines()[0] ) );
  CHECK(  .3 == Approx( data31.cosines()[1] ) );
  CHECK( +1. == Approx( data31.cosines()[2] ) );

  auto data32 = std::get< ThermalScatteringDiscreteCosinesWithProbability >( chunk.discreteCosineData( 3, 2 ) );
  CHECK( 3 == data32.NC() );
  CHECK( 3 == data32.numberDiscreteCosines() );
  CHECK(  8. == Approx( data32.energy() ) );
  CHECK(  .33 == Approx( data32.pdf() ) );
  CHECK(  .5 == Approx( data32.cdf() ) );
  CHECK( -1. == Approx( data32.cosines()[0] ) );
  CHECK(  .7 == Approx( data32.cosines()[1] ) );
  CHECK( +1. == Approx( data32.cosines()[2] ) );

  auto data33 = std::get< ThermalScatteringDiscreteCosinesWithProbability >( chunk.discreteCosineData( 3, 3 ) );
  CHECK( 3 == data33.NC() );
  CHECK( 3 == data33.numberDiscreteCosines() );
  CHECK(  9. == Approx( data33.energy() ) );
  CHECK(  .33 == Approx( data33.pdf() ) );
  CHECK(  1. == Approx( data33.cdf() ) );
  CHECK( -1. == Approx( data33.cosines()[0] ) );
  CHECK(  .6 == Approx( data33.cosines()[1] ) );
  CHECK( +1. == Approx( data33.cosines()[2] ) );

  auto data41 = std::get< ThermalScatteringDiscreteCosinesWithProbability >( chunk.discreteCosineData( 4, 1 ) );
  CHECK( 3 == data41.NC() );
  CHECK( 3 == data41.numberDiscreteCosines() );
  CHECK( 10. == Approx( data41.energy() ) );
  CHECK(  .33 == Approx( data41.pdf() ) );
  CHECK(  0. == Approx( data41.cdf() ) );
  CHECK( -1. == Approx( data41.cosines()[0] ) );
  CHECK(  .2 == Approx( data41.cosines()[1] ) );
  CHECK( +1. == Approx( data41.cosines()[2] ) );

  auto data42 = std::get< ThermalScatteringDiscreteCosinesWithProbability >( chunk.discreteCosineData( 4, 2 ) );
  CHECK( 3 == data42.NC() );
  CHECK( 3 == data42.numberDiscreteCosines() );
  CHECK( 11. == Approx( data42.energy() ) );
  CHECK(  .33 == Approx( data42.pdf() ) );
  CHECK(  .5 == Approx( data42.cdf() ) );
  CHECK( -1. == Approx( data42.cosines()[0] ) );
  CHECK(  .5 == Approx( data42.cosines()[1] ) );
  CHECK( +1. == Approx( data42.cosines()[2] ) );

  auto data43 = std::get< ThermalScatteringDiscreteCosinesWithProbability >( chunk.discreteCosineData( 4, 3 ) );
  CHECK( 3 == data43.NC() );
  CHECK( 3 == data43.numberDiscreteCosines() );
  CHECK( 12. == Approx( data43.energy() ) );
  CHECK(  .33 == Approx( data43.pdf() ) );
  CHECK(  1. == Approx( data43.cdf() ) );
  CHECK( -1. == Approx( data43.cosines()[0] ) );
  CHECK(  .4 == Approx( data43.cosines()[1] ) );
  CHECK( +1. == Approx( data43.cosines()[2] ) );
}
