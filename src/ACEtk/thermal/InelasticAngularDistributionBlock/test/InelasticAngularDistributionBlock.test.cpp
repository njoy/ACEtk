// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/thermal/InelasticAngularDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using InelasticAngularDistributionBlock = thermal::InelasticAngularDistributionBlock;
using DiscreteCosines = thermal::DiscreteCosines;
using DiscreteCosinesWithProbability = thermal::DiscreteCosinesWithProbability;

std::vector< double > chunk();
std::vector< double > chunkWithIFENG2();
void verifyChunk( const InelasticAngularDistributionBlock&, const std::vector< double >& );
void verifyChunkWithIFENG2( const InelasticAngularDistributionBlock&, const std::vector< double >& );
InelasticAngularDistributionBlock makeDummyBlock();

SCENARIO( "InelasticAngularDistributionBlock" ) {

  GIVEN( "valid data for a InelasticAngularDistributionBlock instance using "
         "IFENG = 1" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      bool skewed = true;
      std::vector< std::vector< DiscreteCosines > > cosines = {

        { { 1., { -1.0, -0.9, 1.0 } },
          { 2., { -1.0, 0.0, 1.0 } } },
        { { 3., { -1.0, 0.5, 1.0 } },
          { 4., { -1.0, 0.9, 1.0 } } },
        { { 5., { -1.0, 0.4, 1.0 } },
          { 6., { -1.0, 0.8, 1.0 } } },
        { { 7., { -1.0, 0.3, 1.0 } },
          { 8., { -1.0, 0.7, 1.0 } } }
      };

      InelasticAngularDistributionBlock chunk( std::move( cosines ), skewed );

      THEN( "a InelasticAngularDistributionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      InelasticAngularDistributionBlock
      chunk( 1, 2, 3, 4, 9, xss.begin(), xss.end() );

      THEN( "a InelasticAngularDistributionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      InelasticAngularDistributionBlock chunk( 1, 2, 3, 4, 9, xss.begin(), xss.end() );
      InelasticAngularDistributionBlock copy( chunk );

      THEN( "an InelasticAngularDistributionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      InelasticAngularDistributionBlock chunk( 1, 2, 3, 4, 9, xss.begin(), xss.end() );
      InelasticAngularDistributionBlock move( std::move( chunk ) );

      THEN( "an InelasticAngularDistributionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      InelasticAngularDistributionBlock chunk( 1, 2, 3, 4, 9, xss.begin(), xss.end() );
      InelasticAngularDistributionBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an InelasticAngularDistributionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      InelasticAngularDistributionBlock chunk( 1, 2, 3, 4, 9, xss.begin(), xss.end() );
      InelasticAngularDistributionBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an InelasticAngularDistributionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a InelasticAngularDistributionBlock "
         "instance using IFENG = 2" ) {

    std::vector< double > xss = chunkWithIFENG2();

    WHEN( "the data is given explicitly" ) {

      std::vector< std::vector< DiscreteCosinesWithProbability > > cosines = {

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

      InelasticAngularDistributionBlock chunk( std::move( cosines ), 9 );

      THEN( "a InelasticAngularDistributionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunkWithIFENG2( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      InelasticAngularDistributionBlock
      chunk( 2, 0, 3, 4, 9, xss.begin(), xss.end() );

      THEN( "a InelasticAngularDistributionBlock can be constructed "
            "and members can be tested" ) {

        verifyChunkWithIFENG2( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      InelasticAngularDistributionBlock chunk( 2, 0, 3, 4, 9, xss.begin(), xss.end() );
      InelasticAngularDistributionBlock copy( chunk );

      THEN( "an InelasticAngularDistributionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunkWithIFENG2( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      InelasticAngularDistributionBlock chunk( 2, 0, 3, 4, 9, xss.begin(), xss.end() );
      InelasticAngularDistributionBlock move( std::move( chunk ) );

      THEN( "an InelasticAngularDistributionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunkWithIFENG2( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      InelasticAngularDistributionBlock chunk( 2, 0, 3, 4, 9, xss.begin(), xss.end() );
      InelasticAngularDistributionBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an InelasticAngularDistributionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunkWithIFENG2( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      InelasticAngularDistributionBlock chunk( 2, 0, 3, 4, 9, xss.begin(), xss.end() );
      InelasticAngularDistributionBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an InelasticAngularDistributionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunkWithIFENG2( move, xss );
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

                    16,                 28,                 52,                 70,
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

void verifyChunk( const InelasticAngularDistributionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 32 == chunk.length() );
  CHECK( "InelasticAngularDistributionBlock" == chunk.name() );

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

  auto data11 = std::get< DiscreteCosines >( chunk.discreteCosineData( 1, 1 ) );
  CHECK( 3 == data11.NC() );
  CHECK( 3 == data11.numberDiscreteCosines() );
  CHECK_THAT( 1., WithinRel( data11.energy() ) );
  CHECK_THAT( -1., WithinRel( data11.cosines()[0] ) );
  CHECK_THAT( -.9, WithinRel( data11.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data11.cosines()[2] ) );

  auto data12 = std::get< DiscreteCosines >( chunk.discreteCosineData( 1, 2 ) );
  CHECK( 3 == data12.NC() );
  CHECK( 3 == data12.numberDiscreteCosines() );
  CHECK_THAT( 2., WithinRel( data12.energy() ) );
  CHECK_THAT( -1., WithinRel( data12.cosines()[0] ) );
  CHECK_THAT(  0., WithinRel( data12.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data12.cosines()[2] ) );

  auto data21 = std::get< DiscreteCosines >( chunk.discreteCosineData( 2, 1 ) );
  CHECK( 3 == data21.NC() );
  CHECK( 3 == data21.numberDiscreteCosines() );
  CHECK_THAT( 3., WithinRel( data21.energy() ) );
  CHECK_THAT( -1., WithinRel( data21.cosines()[0] ) );
  CHECK_THAT(  .5, WithinRel( data21.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data21.cosines()[2] ) );

  auto data22 = std::get< DiscreteCosines >( chunk.discreteCosineData( 2, 2 ) );
  CHECK( 3 == data22.NC() );
  CHECK( 3 == data22.numberDiscreteCosines() );
  CHECK_THAT( 4., WithinRel( data22.energy() ) );
  CHECK_THAT( -1., WithinRel( data22.cosines()[0] ) );
  CHECK_THAT(  .9, WithinRel( data22.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data22.cosines()[2] ) );

  auto data31 = std::get< DiscreteCosines >( chunk.discreteCosineData( 3, 1 ) );
  CHECK( 3 == data31.NC() );
  CHECK( 3 == data31.numberDiscreteCosines() );
  CHECK_THAT( 5., WithinRel( data31.energy() ) );
  CHECK_THAT( -1., WithinRel( data31.cosines()[0] ) );
  CHECK_THAT(  .4, WithinRel( data31.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data31.cosines()[2] ) );

  auto data32 = std::get< DiscreteCosines >( chunk.discreteCosineData( 3, 2 ) );
  CHECK( 3 == data32.NC() );
  CHECK( 3 == data32.numberDiscreteCosines() );
  CHECK_THAT( 6., WithinRel( data32.energy() ) );
  CHECK_THAT( -1., WithinRel( data32.cosines()[0] ) );
  CHECK_THAT(  .8, WithinRel( data32.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data32.cosines()[2] ) );

  auto data41 = std::get< DiscreteCosines >( chunk.discreteCosineData( 4, 1 ) );
  CHECK( 3 == data41.NC() );
  CHECK( 3 == data41.numberDiscreteCosines() );
  CHECK_THAT( 7., WithinRel( data41.energy() ) );
  CHECK_THAT( -1., WithinRel( data41.cosines()[0] ) );
  CHECK_THAT(  .3, WithinRel( data41.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data41.cosines()[2] ) );

  auto data42 = std::get< DiscreteCosines >( chunk.discreteCosineData( 4, 2 ) );
  CHECK( 3 == data42.NC() );
  CHECK( 3 == data42.numberDiscreteCosines() );
  CHECK_THAT( 8., WithinRel( data42.energy() ) );
  CHECK_THAT( -1., WithinRel( data42.cosines()[0] ) );
  CHECK_THAT(  .7, WithinRel( data42.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data42.cosines()[2] ) );
}

void verifyChunkWithIFENG2( const InelasticAngularDistributionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 80 == chunk.length() );
  CHECK( "InelasticAngularDistributionBlock" == chunk.name() );

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

  auto data11 = std::get< DiscreteCosinesWithProbability >( chunk.discreteCosineData( 1, 1 ) );
  CHECK( 3 == data11.NC() );
  CHECK( 3 == data11.numberDiscreteCosines() );
  CHECK_THAT(  1., WithinRel( data11.energy() ) );
  CHECK_THAT(  .5, WithinRel( data11.pdf() ) );
  CHECK_THAT(  .0, WithinRel( data11.cdf() ) );
  CHECK_THAT( -1., WithinRel( data11.cosines()[0] ) );
  CHECK_THAT( -.9, WithinRel( data11.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data11.cosines()[2] ) );

  auto data12 = std::get< DiscreteCosinesWithProbability >( chunk.discreteCosineData( 1, 2 ) );
  CHECK( 3 == data12.NC() );
  CHECK( 3 == data12.numberDiscreteCosines() );
  CHECK_THAT(  2., WithinRel( data12.energy() ) );
  CHECK_THAT(  .5, WithinRel( data12.pdf() ) );
  CHECK_THAT(  1., WithinRel( data12.cdf() ) );
  CHECK_THAT( -1., WithinRel( data12.cosines()[0] ) );
  CHECK_THAT(  0., WithinRel( data12.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data12.cosines()[2] ) );

  auto data21 = std::get< DiscreteCosinesWithProbability >( chunk.discreteCosineData( 2, 1 ) );
  CHECK( 3 == data21.NC() );
  CHECK( 3 == data21.numberDiscreteCosines() );
  CHECK_THAT(  3., WithinRel( data21.energy() ) );
  CHECK_THAT(  .25, WithinRel( data21.pdf() ) );
  CHECK_THAT(  0., WithinRel( data21.cdf() ) );
  CHECK_THAT( -1., WithinRel( data21.cosines()[0] ) );
  CHECK_THAT(  .5, WithinRel( data21.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data21.cosines()[2] ) );

  auto data22 = std::get< DiscreteCosinesWithProbability >( chunk.discreteCosineData( 2, 2 ) );
  CHECK( 3 == data22.NC() );
  CHECK( 3 == data22.numberDiscreteCosines() );
  CHECK_THAT(  4., WithinRel( data22.energy() ) );
  CHECK_THAT(  .25, WithinRel( data22.pdf() ) );
  CHECK_THAT(  0.33, WithinRel( data22.cdf() ) );
  CHECK_THAT( -1., WithinRel( data22.cosines()[0] ) );
  CHECK_THAT(  .9, WithinRel( data22.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data22.cosines()[2] ) );

  auto data23 = std::get< DiscreteCosinesWithProbability >( chunk.discreteCosineData( 2, 3 ) );
  CHECK( 3 == data23.NC() );
  CHECK( 3 == data23.numberDiscreteCosines() );
  CHECK_THAT(  5., WithinRel( data23.energy() ) );
  CHECK_THAT(  .25, WithinRel( data23.pdf() ) );
  CHECK_THAT(  0.66, WithinRel( data23.cdf() ) );
  CHECK_THAT( -1., WithinRel( data23.cosines()[0] ) );
  CHECK_THAT(  .4, WithinRel( data23.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data23.cosines()[2] ) );

  auto data24 = std::get< DiscreteCosinesWithProbability >( chunk.discreteCosineData( 2, 4 ) );
  CHECK( 3 == data24.NC() );
  CHECK( 3 == data24.numberDiscreteCosines() );
  CHECK_THAT(  6., WithinRel( data24.energy() ) );
  CHECK_THAT(  .25, WithinRel( data24.pdf() ) );
  CHECK_THAT(  1., WithinRel( data24.cdf() ) );
  CHECK_THAT( -1., WithinRel( data24.cosines()[0] ) );
  CHECK_THAT(  .8, WithinRel( data24.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data24.cosines()[2] ) );

  auto data31 = std::get< DiscreteCosinesWithProbability >( chunk.discreteCosineData( 3, 1 ) );
  CHECK( 3 == data31.NC() );
  CHECK( 3 == data31.numberDiscreteCosines() );
  CHECK_THAT(  7., WithinRel( data31.energy() ) );
  CHECK_THAT(  .33, WithinRel( data31.pdf() ) );
  CHECK_THAT(  0., WithinRel( data31.cdf() ) );
  CHECK_THAT( -1., WithinRel( data31.cosines()[0] ) );
  CHECK_THAT(  .3, WithinRel( data31.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data31.cosines()[2] ) );

  auto data32 = std::get< DiscreteCosinesWithProbability >( chunk.discreteCosineData( 3, 2 ) );
  CHECK( 3 == data32.NC() );
  CHECK( 3 == data32.numberDiscreteCosines() );
  CHECK_THAT(  8., WithinRel( data32.energy() ) );
  CHECK_THAT(  .33, WithinRel( data32.pdf() ) );
  CHECK_THAT(  .5, WithinRel( data32.cdf() ) );
  CHECK_THAT( -1., WithinRel( data32.cosines()[0] ) );
  CHECK_THAT(  .7, WithinRel( data32.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data32.cosines()[2] ) );

  auto data33 = std::get< DiscreteCosinesWithProbability >( chunk.discreteCosineData( 3, 3 ) );
  CHECK( 3 == data33.NC() );
  CHECK( 3 == data33.numberDiscreteCosines() );
  CHECK_THAT(  9., WithinRel( data33.energy() ) );
  CHECK_THAT(  .33, WithinRel( data33.pdf() ) );
  CHECK_THAT(  1., WithinRel( data33.cdf() ) );
  CHECK_THAT( -1., WithinRel( data33.cosines()[0] ) );
  CHECK_THAT(  .6, WithinRel( data33.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data33.cosines()[2] ) );

  auto data41 = std::get< DiscreteCosinesWithProbability >( chunk.discreteCosineData( 4, 1 ) );
  CHECK( 3 == data41.NC() );
  CHECK( 3 == data41.numberDiscreteCosines() );
  CHECK_THAT( 10., WithinRel( data41.energy() ) );
  CHECK_THAT(  .33, WithinRel( data41.pdf() ) );
  CHECK_THAT(  0., WithinRel( data41.cdf() ) );
  CHECK_THAT( -1., WithinRel( data41.cosines()[0] ) );
  CHECK_THAT(  .2, WithinRel( data41.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data41.cosines()[2] ) );

  auto data42 = std::get< DiscreteCosinesWithProbability >( chunk.discreteCosineData( 4, 2 ) );
  CHECK( 3 == data42.NC() );
  CHECK( 3 == data42.numberDiscreteCosines() );
  CHECK_THAT( 11., WithinRel( data42.energy() ) );
  CHECK_THAT(  .33, WithinRel( data42.pdf() ) );
  CHECK_THAT(  .5, WithinRel( data42.cdf() ) );
  CHECK_THAT( -1., WithinRel( data42.cosines()[0] ) );
  CHECK_THAT(  .5, WithinRel( data42.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data42.cosines()[2] ) );

  auto data43 = std::get< DiscreteCosinesWithProbability >( chunk.discreteCosineData( 4, 3 ) );
  CHECK( 3 == data43.NC() );
  CHECK( 3 == data43.numberDiscreteCosines() );
  CHECK_THAT( 12., WithinRel( data43.energy() ) );
  CHECK_THAT(  .33, WithinRel( data43.pdf() ) );
  CHECK_THAT(  1., WithinRel( data43.cdf() ) );
  CHECK_THAT( -1., WithinRel( data43.cosines()[0] ) );
  CHECK_THAT(  .4, WithinRel( data43.cosines()[1] ) );
  CHECK_THAT( +1., WithinRel( data43.cosines()[2] ) );
}

InelasticAngularDistributionBlock makeDummyBlock() {

  return { { { { 1., { -1., 1. } }, { 2., { -1., 1. } } },
             { { 1., { -1., 1. } }, { 3., { -1., 1. } } } }, true };
}
