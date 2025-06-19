// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/SecondaryParticleAngularDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using SecondaryParticleAngularDistributionBlock = continuous::SecondaryParticleAngularDistributionBlock;
using AngularDistributionData = continuous::AngularDistributionData;
using FullyIsotropicDistribution = continuous::FullyIsotropicDistribution;
using DistributionGivenElsewhere = continuous::DistributionGivenElsewhere;
using DistributionData = continuous::SecondaryParticleAngularDistributionBlock::DistributionData;
using TabulatedAngularDistribution = continuous::TabulatedAngularDistribution;
using IsotropicAngularDistribution = continuous::IsotropicAngularDistribution;

std::vector< double > chunk();
void verifyChunk( const SecondaryParticleAngularDistributionBlock&, const std::vector< double >& );
SecondaryParticleAngularDistributionBlock makeDummyBlock();

SCENARIO( "SecondaryParticleAngularDistributionBlock" ) {

   GIVEN( "valid data for a SecondaryParticleAngularDistributionBlock instance" ) {

     std::vector< double > xss = chunk();

     WHEN( "the data is given explicitly" ) {

       std::vector< DistributionData > distributions = {

         AngularDistributionData(
           { TabulatedAngularDistribution( 1e-11, 2, { -1.0, 1.0 },
                                           { 0.5, 0.5 }, { 0.0, 1.0 } ),
             TabulatedAngularDistribution( 20., 2, { -1.0, 0.0, 1.0 },
                                           { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ) } ),
         DistributionGivenElsewhere(),
         FullyIsotropicDistribution(),
         AngularDistributionData(
           { TabulatedAngularDistribution( 1e-11, 2, { -1.0, 0.0, 1.0 },
                                           { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ),
             IsotropicAngularDistribution( 1. ),
             TabulatedAngularDistribution( 20., 2, { -1.0, 1.0 },
                                           { 0.5, 0.5 }, { 0.0, 1.0 } ) } )
       };

       SecondaryParticleAngularDistributionBlock chunk( std::move( distributions ) );

       THEN( "a SecondaryParticleAngularDistributionBlock can be constructed "
             "and members can be tested" ) {

         verifyChunk( chunk, xss );
       } // THEN
     } // WHEN

     WHEN( "the data is defined by iterators" ) {

       SecondaryParticleAngularDistributionBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 4 );

       THEN( "a SecondaryParticleAngularDistributionBlock can be constructed "
             "and members can be tested" ) {

         verifyChunk( chunk, xss );
       } // THEN
     } // WHEN

    WHEN( "using the copy constructor" ) {

      SecondaryParticleAngularDistributionBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 4 );
      SecondaryParticleAngularDistributionBlock copy( chunk );

      THEN( "an SecondaryParticleAngularDistributionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      SecondaryParticleAngularDistributionBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 4 );
      SecondaryParticleAngularDistributionBlock move( std::move( chunk ) );

      THEN( "an SecondaryParticleAngularDistributionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      SecondaryParticleAngularDistributionBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 4 );
      SecondaryParticleAngularDistributionBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an SecondaryParticleAngularDistributionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      SecondaryParticleAngularDistributionBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 4 );
      SecondaryParticleAngularDistributionBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an SecondaryParticleAngularDistributionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  // 4 reactions:
  //   - first and last reaction have data given
  //   - second one is given elsewhere
  //   - third one is fully isotropic
  // the given data:
  //   - for reaction 1 : 2 incident energies, both tabulated data
  //   - for reaction 4 : 3 incident energies, tabulated, isotropic, tabulated
  return {                 1,                 -1,                  0,                 25,
                           2,  1.00000000000E-11,  2.00000000000E+01,                 -6,
                         -14,                  2,                  2, -1.00000000000E+00,
           1.00000000000E+00,  5.00000000000E-01,  5.00000000000E-01,  0.00000000000E+00,
           1.00000000000E+00,                  2,                  3, -1.00000000000E+00,
           0.00000000000E+00,  1.00000000000E+00,  5.00000000000E-01,  5.00000000000E-01,
           5.00000000000E-01,  0.00000000000E+00,  5.00000000000E-01,  1.00000000000E+00,
                           3,  1.00000000000E-11,  1.00000000000E+00,  2.00000000000E+01,
                         -32,                  0,                -43,                  2,
                           3, -1.00000000000E+00,  0.00000000000E+00,  1.00000000000E+00,
           5.00000000000E-01,  5.00000000000E-01,  5.00000000000E-01,  0.00000000000E+00,
           5.00000000000E-01,  1.00000000000E+00,                  2,                  2,
          -1.00000000000E+00,  1.00000000000E+00,  5.00000000000E-01,  5.00000000000E-01,
           0.00000000000E+00,  1.00000000000E+00 };
}

void verifyChunk( const SecondaryParticleAngularDistributionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 54 == chunk.length() );
  CHECK( "ANDH" == chunk.name() );

  CHECK( 4 == chunk.NR() );
  CHECK( 4 == chunk.numberReactions() );
  CHECK( 4 == chunk.data().size() );

  CHECK( 1 == chunk.LAND(1) );
  CHECK( -1 == chunk.LAND(2) );
  CHECK( 0 == chunk.LAND(3) );
  CHECK( 25 == chunk.LAND(4) );
  CHECK( 1 == chunk.angularDistributionLocator(1) );
  CHECK( -1 == chunk.angularDistributionLocator(2) );
  CHECK( 0 == chunk.angularDistributionLocator(3) );
  CHECK( 25 == chunk.angularDistributionLocator(4) );

  CHECK( false == chunk.isFullyIsotropic(1) );
  CHECK( false == chunk.isFullyIsotropic(2) );
  CHECK( true == chunk.isFullyIsotropic(3) );
  CHECK( false == chunk.isFullyIsotropic(4) );

  CHECK( true == chunk.isGiven(1) );
  CHECK( false == chunk.isGiven(2) );
  CHECK( true == chunk.isGiven(3) );
  CHECK( true == chunk.isGiven(4) );

  CHECK( true == std::holds_alternative< AngularDistributionData >( chunk.angularDistributionData(1) ) );
  CHECK( true == std::holds_alternative< DistributionGivenElsewhere >( chunk.angularDistributionData(2) ) );
  CHECK( true == std::holds_alternative< FullyIsotropicDistribution >( chunk.angularDistributionData(3) ) );
  CHECK( true == std::holds_alternative< AngularDistributionData >( chunk.angularDistributionData(4) ) );

  auto data1 = std::get< AngularDistributionData >( chunk.angularDistributionData(1) );
  CHECK( 2 == data1.NE() );
  CHECK( 2 == data1.numberIncidentEnergies() );
  CHECK( 2 == data1.incidentEnergies().size() );
  CHECK_THAT( 1e-11, WithinRel( data1.incidentEnergies()[0] ) );
  CHECK_THAT( 20., WithinRel( data1.incidentEnergies()[1] ) );
  CHECK_THAT( 1e-11, WithinRel( data1.incidentEnergy(1) ) );
  CHECK_THAT( 20., WithinRel( data1.incidentEnergy(2) ) );
  CHECK( -6 == data1.LOCC(1) );
  CHECK( -14 == data1.LOCC(2) );
  CHECK( -6 == data1.distributionLocator(1) );
  CHECK( -14 == data1.distributionLocator(2) );
  CHECK( AngularDistributionType::Tabulated == data1.distributionType(1) );
  CHECK( AngularDistributionType::Tabulated == data1.distributionType(2) );
  CHECK( 6 == data1.relativeDistributionLocator(1) );
  CHECK( 14 == data1.relativeDistributionLocator(2) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistribution >( data1.distribution(1) ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistribution >( data1.distribution(2) ) );

  auto data4 = std::get< AngularDistributionData >( chunk.angularDistributionData(4) );
  CHECK( 3 == data4.NE() );
  CHECK( 3 == data4.numberIncidentEnergies() );
  CHECK( 3 == data4.incidentEnergies().size() );
  CHECK_THAT( 1e-11, WithinRel( data4.incidentEnergies()[0] ) );
  CHECK_THAT( 1., WithinRel( data4.incidentEnergies()[1] ) );
  CHECK_THAT( 20., WithinRel( data4.incidentEnergies()[2] ) );
  CHECK_THAT( 1e-11, WithinRel( data4.incidentEnergy(1) ) );
  CHECK_THAT( 1., WithinRel( data4.incidentEnergy(2) ) );
  CHECK_THAT( 20., WithinRel( data4.incidentEnergy(3) ) );
  CHECK( -32 == data4.LOCC(1) );
  CHECK( 0 == data4.LOCC(2) );
  CHECK( -43 == data4.LOCC(3) );
  CHECK( -32 == data4.distributionLocator(1) );
  CHECK( 0 == data4.distributionLocator(2) );
  CHECK( -43 == data4.distributionLocator(3) );
  CHECK( AngularDistributionType::Tabulated == data4.distributionType(1) );
  CHECK( AngularDistributionType::Isotropic == data4.distributionType(2) );
  CHECK( AngularDistributionType::Tabulated == data4.distributionType(3) );
  CHECK( 8 == data4.relativeDistributionLocator(1) );
  CHECK( 0 == data4.relativeDistributionLocator(2) );
  CHECK( 19 == data4.relativeDistributionLocator(3) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistribution >( data4.distribution(1) ) );
  CHECK( true == std::holds_alternative< IsotropicAngularDistribution >( data4.distribution(2) ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistribution >( data4.distribution(3) ) );
}

SecondaryParticleAngularDistributionBlock makeDummyBlock() {

  return { { DistributionGivenElsewhere(), FullyIsotropicDistribution() } };
}
