#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/continuous/AngularDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using AngularDistributionBlock = block::AngularDistributionBlock;
using AngularDistributionData = block::AngularDistributionData;
using FullyIsotropicDistribution = block::FullyIsotropicDistribution;
using DistributionGivenElsewhere = block::DistributionGivenElsewhere;
using DistributionData = block::AngularDistributionBlock::DistributionData;
using TabulatedAngularDistribution = block::TabulatedAngularDistribution;
using IsotropicAngularDistribution = block::IsotropicAngularDistribution;

std::vector< double > chunk();
void verifyChunk( const AngularDistributionBlock& );

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

      AngularDistributionBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 3 );

      THEN( "a AngularDistributionBlock can be constructed and members can be tested" ) {

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

void verifyChunk( const AngularDistributionBlock& chunk ) {

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
  CHECK( 1e-11 == Approx( data1.incidentEnergies()[0] ) );
  CHECK( 20. == Approx( data1.incidentEnergies()[1] ) );
  CHECK( 1e-11 == Approx( data1.incidentEnergy(1) ) );
  CHECK( 20. == Approx( data1.incidentEnergy(2) ) );
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
  CHECK( 1e-11 == Approx( data4.incidentEnergies()[0] ) );
  CHECK( 1. == Approx( data4.incidentEnergies()[1] ) );
  CHECK( 20. == Approx( data4.incidentEnergies()[2] ) );
  CHECK( 1e-11 == Approx( data4.incidentEnergy(1) ) );
  CHECK( 1. == Approx( data4.incidentEnergy(2) ) );
  CHECK( 20. == Approx( data4.incidentEnergy(3) ) );
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
