// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/AngularDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using AngularDistributionBlock = continuous::AngularDistributionBlock;
using AngularDistributionData = continuous::AngularDistributionData;
using FullyIsotropicDistribution = continuous::FullyIsotropicDistribution;
using DistributionGivenElsewhere = continuous::DistributionGivenElsewhere;
using DistributionData = continuous::AngularDistributionBlock::DistributionData;
using TabulatedAngularDistribution = continuous::TabulatedAngularDistribution;
using IsotropicAngularDistribution = continuous::IsotropicAngularDistribution;

std::vector< double > chunk();
void verifyChunk( const AngularDistributionBlock&, const std::vector< double >& );
AngularDistributionBlock makeDummyBlock();

SCENARIO( "AngularDistributionBlock" ) {

  GIVEN( "valid data for a AngularDistributionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      DistributionData elastic =
        AngularDistributionData(
          { TabulatedAngularDistribution( 1e-11, 2, { -1.0, 1.0 },
                                          { 0.5, 0.5 }, { 0.0, 1.0 } ),
            TabulatedAngularDistribution( 20., 2, { -1.0, 0.0, 1.0 },
                                          { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ) } );

      std::vector< DistributionData > distributions = {

        DistributionGivenElsewhere(),
        FullyIsotropicDistribution(),
        AngularDistributionData(
          { TabulatedAngularDistribution( 1e-11, 2, { -1.0, 0.0, 1.0 },
                                          { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ),
            IsotropicAngularDistribution( 1. ),
            TabulatedAngularDistribution( 20., 2, { -1.0, 1.0 },
                                          { 0.5, 0.5 }, { 0.0, 1.0 } ) } )
      };

      AngularDistributionBlock chunk( std::move( elastic ),
                                      std::move( distributions ) );

      THEN( "a AngularDistributionBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      AngularDistributionBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 3 );

      THEN( "a AngularDistributionBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      AngularDistributionBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 3 );
      AngularDistributionBlock copy( chunk );

      THEN( "a AngularDistributionBlock can be constructed and members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      AngularDistributionBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 3 );
      AngularDistributionBlock move( std::move( chunk ) );

      THEN( "a AngularDistributionBlock can be constructed and members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      AngularDistributionBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 3 );
      AngularDistributionBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "a AngularDistributionBlock can be constructed and members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      AngularDistributionBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 3 );
      AngularDistributionBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "a AngularDistributionBlock can be constructed and members can be tested" ) {

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

void verifyChunk( const AngularDistributionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 54 == chunk.length() );
  CHECK( "AND" == chunk.name() );

  CHECK( 3 == chunk.NR() );
  CHECK( 3 == chunk.numberProjectileProductionReactions() );
  CHECK( 4 == chunk.totalNumberProjectileProductionReactions() );
  CHECK( 4 == chunk.data().size() );

  CHECK( 1 == chunk.LAND(0) ); // elastic
  CHECK( -1 == chunk.LAND(1) );
  CHECK( 0 == chunk.LAND(2) );
  CHECK( 25 == chunk.LAND(3) );
  CHECK( 1 == chunk.angularDistributionLocator(0) ); // elastic
  CHECK( -1 == chunk.angularDistributionLocator(1) );
  CHECK( 0 == chunk.angularDistributionLocator(2) );
  CHECK( 25 == chunk.angularDistributionLocator(3) );

  CHECK( false == chunk.isFullyIsotropic(0) ); // elastic
  CHECK( false == chunk.isFullyIsotropic(1) );
  CHECK( true == chunk.isFullyIsotropic(2) );
  CHECK( false == chunk.isFullyIsotropic(3) );

  CHECK( true == chunk.isGiven(0) ); // elastic
  CHECK( false == chunk.isGiven(1) );
  CHECK( true == chunk.isGiven(2) );
  CHECK( true == chunk.isGiven(3) );

  CHECK( true == std::holds_alternative< AngularDistributionData >( chunk.angularDistributionData(0) ) ); // elastic
  CHECK( true == std::holds_alternative< DistributionGivenElsewhere >( chunk.angularDistributionData(1) ) );
  CHECK( true == std::holds_alternative< FullyIsotropicDistribution >( chunk.angularDistributionData(2) ) );
  CHECK( true == std::holds_alternative< AngularDistributionData >( chunk.angularDistributionData(3) ) );

  auto data1 = std::get< AngularDistributionData >( chunk.angularDistributionData(0) ); // elastic
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

  auto data4 = std::get< AngularDistributionData >( chunk.angularDistributionData(3) );
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

AngularDistributionBlock makeDummyBlock() {

  DistributionData elastic =
    AngularDistributionData(
      { TabulatedAngularDistribution( 1e-5, 2, { -1.0, 1.0 },
                                      { 0.5, 0.5 }, { 0.0, 1.0 } ),
        TabulatedAngularDistribution( 20e+6, 2, { -1.0, 0.0, 1.0 },
                                      { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ) } );

  std::vector< DistributionData > distributions = {

    FullyIsotropicDistribution()
  };

  return { std::move( elastic ), std::move( distributions ) };
}