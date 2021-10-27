#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/EnergyDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EnergyDistributionBlock = block::EnergyDistributionBlock;
using LevelScatteringDistribution = block::LevelScatteringDistribution;
using OutgoingEnergyDistributionData = block::OutgoingEnergyDistributionData;
using KalbachMannDistributionData = block::KalbachMannDistributionData;

std::vector< double > chunk();
void verifyChunk( const EnergyDistributionBlock& );

SCENARIO( "EnergyDistributionBlock" ) {

  GIVEN( "valid data for an EnergyDistributionBlock instance" ) {

    std::vector< double > xss = chunk();

//    WHEN( "the data is given explicitly" ) {
//
//      std::vector< DistributionData > distributions = {
//
//        AngularDistributionData(
//          { TabulatedAngularDistribution( 1e-11, 2, { -1.0, 1.0 },
//                                          { 0.5, 0.5 }, { 0.0, 1.0 } ),
//            TabulatedAngularDistribution( 20., 2, { -1.0, 0.0, 1.0 },
//                                          { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ) } ),
//        DistributionGivenElsewhere(),
//        FullyIsotropicDistribution(),
//        AngularDistributionData(
//          { TabulatedAngularDistribution( 1e-11, 2, { -1.0, 0.0, 1.0 },
//                                          { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ),
//            IsotropicAngularDistribution( 1. ),
//            TabulatedAngularDistribution( 20., 2, { -1.0, 1.0 },
//                                          { 0.5, 0.5 }, { 0.0, 1.0 } ) } )
//      };
//
//      EnergyDistributionBlock chunk( std::move( distributions ) );
//
//      THEN( "an EnergyDistributionBlock can be constructed and members can be tested" ) {
//
//        verifyChunk( chunk );
//      } // THEN
//
//      THEN( "the XSS array is correct" ) {
//
//        auto xss_chunk = chunk.XSS();
//        for ( unsigned int i = 0; i < chunk.length(); ++i ) {
//
//          CHECK( xss[i] == Approx( xss_chunk[i] ) );
//        }
//      } // THEN
//    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      EnergyDistributionBlock chunk( xss.begin(), xss.begin() + 2, xss.end(), 2 );

      THEN( "an EnergyDistributionBlock can be constructed and members can be tested" ) {

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

  // 2 reactions
  // the given data:
  //   - for reaction 1 : 1 law -> level scattering data
  //   - for reaction 2 : 1 law -> Kalbach-Mann systematics for two incident energies
  return {
           // LDLW
                           1,                 12,
           // DLW - reaction 1 - LNW = 0, LAW = 3, IDAT = 10
                           0,                  3,                 10,                  0,
                           2,        2.249999e-3,  2.00000000000E+01,  1.00000000000E+00,
           1.00000000000E+00,  7.71295800000E-05,           .9914722,
           // DLW - reaction 1 - LNW = 0, LAW = 44, IDAT = 21
                           0,                 44,                 21,                  0,
                           2,  1.00000000000E-11,  2.00000000000E+01,  1.00000000000E+00,
           1.00000000000E+00,                  0,                  2,       1.219437E+01,
                2.000000E+01,                 27,                 39,                  1,
                           2,       0.000000E+00,       1.866919E-02,       5.356419E+01,
                0.000000E+00,       0.000000E+00,       1.000000E+00,       0.000000E+00,
                0.000000E+00,       2.391154E-01,       2.398743E-01,                  2,
                           3,       0.000000E+00,       1.120151E+00,       7.592137E+00,
                7.738696E-02,       4.209016E-01,       1.226090E-11,       0.000000E+00,
                5.382391E-01,       1.000000E+00,       2.491475E-03,       1.510768E-02,
                9.775367E-01,       2.391154E-01,       2.847920E-01,       5.592013E-01 };
}

void verifyChunk( const EnergyDistributionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 57 == chunk.length() );
  CHECK( "DLW" == chunk.name() );

  CHECK( 2 == chunk.NR() );
  CHECK( 2 == chunk.numberProjectileProductionReactions() );

  CHECK( 1 == chunk.LDLW(1) );
  CHECK( 12 == chunk.LDLW(2) );
  CHECK( 1 == chunk.energyDistributionLocator(1) );
  CHECK( 12 == chunk.energyDistributionLocator(2) );

  CHECK( true == std::holds_alternative< LevelScatteringDistribution >( chunk.energyDistributionData(1) ) );
  CHECK( true == std::holds_alternative< KalbachMannDistributionData >( chunk.energyDistributionData(2) ) );

  auto data1 = std::get< LevelScatteringDistribution >( chunk.energyDistributionData(1) );
  CHECK( EnergyDistributionType::LevelScattering == data1.LAW() );
  CHECK( EnergyDistributionType::LevelScattering == data1.type() );
  CHECK( 2.249999e-3 == Approx( data1.minimumIncidentEnergy() ) );
  CHECK( 20. == Approx( data1.maximumIncidentEnergy() ) );
  CHECK( 7.71295800000E-05 == Approx( data1.C1() ) );
  CHECK( .9914722 == Approx( data1.C2() ) );

  auto data2 = std::get< KalbachMannDistributionData >( chunk.energyDistributionData(2) );
}
