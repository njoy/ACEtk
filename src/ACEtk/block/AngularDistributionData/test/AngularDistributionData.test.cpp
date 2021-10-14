#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/AngularDistributionData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using AngularDistributionData = block::AngularDistributionData;
using IsotropicAngularDistribution = block::IsotropicAngularDistribution;
using EquiprobableAngularBins = block::EquiprobableAngularBins;
using TabulatedAngularDistribution = block::TabulatedAngularDistribution;
using Distribution = AngularDistributionData::Distribution;

std::vector< double > chunk();
void verifyChunk( const AngularDistributionData& );

SCENARIO( "AngularDistributionData" ) {

  GIVEN( "valid data for an AngularDistributionData instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< Distribution > distributions = {

        IsotropicAngularDistribution( 1e-11 ),
        EquiprobableAngularBins(
          1.,
          { -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.3, -0.2, -0.1, 0.0,
            0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5,
            0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.925, 0.95,
            0.9625, 0.975, 1.0 } ),
        TabulatedAngularDistribution(
          20., 2, { -1.0, 0.0, 1.0 }, { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } )
      };
      int locb = 6;

      AngularDistributionData chunk( std::move( distributions ), locb );

      THEN( "an AngularDistributionData can be constructed and members can be "
            "tested" ) {

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

      AngularDistributionData chunk( 6, xss.begin(), xss.end() );

      THEN( "an AngularDistributionData can be constructed and members can be "
            "tested" ) {

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

  // distribution for three incident energy values:
  //   - at 1e-5 eV: isotropic
  //   - at 1 MeV: 32 equiprobable cosine bins
  //   - at 20 MeV: tabulated
  return {                  3,
            1.00000000000E-11,  1.00000000000E+00, 2.00000000000E+01,
                            0,                 13,               -46,
           -1.00000000000E+00, -0.90000000000E+00, -0.80000000000E+00, -0.70000000000E+00,
           -0.60000000000E+00, -0.50000000000E+00, -0.30000000000E+00, -0.20000000000E+00,
           -0.10000000000E+00,  0.00000000000E+00,  0.05000000000E+00,  0.10000000000E+00,
            0.15000000000E+00,  0.20000000000E+00,  0.25000000000E+00,  0.30000000000E+00,
            0.35000000000E+00,  0.40000000000E+00,  0.45000000000E+00,  0.50000000000E+00,
            0.55000000000E+00,  0.60000000000E+00,  0.65000000000E+00,  0.70000000000E+00,
            0.75000000000E+00,  0.80000000000E+00,  0.85000000000E+00,  0.90000000000E+00,
            0.92500000000E+00,  0.95000000000E+00,  0.96250000000E+00,  0.97500000000E+00,
            1.00000000000E+00,                  2,                  3,
           -1.00000000000E+00,  0.00000000000E+00,  1.00000000000E+00,  5.00000000000E-01,
            5.00000000000E-01,  5.00000000000E-01,  0.00000000000E+00,  5.00000000000E-01,
            1.00000000000E+00 };
}

void verifyChunk( const AngularDistributionData& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 51 == chunk.length() );
  CHECK( "AND::AngularDistributionData" == chunk.name() );

  CHECK( 3 == chunk.NE() );
  CHECK( 3 == chunk.numberIncidentEnergies() );

  CHECK( 3 == chunk.incidentEnergies().size() );
  CHECK( 1e-11 == Approx( chunk.incidentEnergies()[0] ) );
  CHECK( 1. == Approx( chunk.incidentEnergies()[1] ) );
  CHECK( 20. == Approx( chunk.incidentEnergies()[2] ) );

  CHECK( 1e-11 == Approx( chunk.incidentEnergy(1) ) );
  CHECK( 1. == Approx( chunk.incidentEnergy(2) ) );
  CHECK( 20. == Approx( chunk.incidentEnergy(3) ) );

  CHECK( 0 == chunk.LOCC(1) );
  CHECK( 13 == chunk.LOCC(2) );
  CHECK( -46 == chunk.LOCC(3) );
  CHECK( 0 == chunk.angularDistributionLocator(1) );
  CHECK( 13 == chunk.angularDistributionLocator(2) );
  CHECK( -46 == chunk.angularDistributionLocator(3) );

  CHECK( AngularDistributionType::Isotropic == chunk.angularDistributionType(1) );
  CHECK( AngularDistributionType::Equiprobable == chunk.angularDistributionType(2) );
  CHECK( AngularDistributionType::Tabulated == chunk.angularDistributionType(3) );
  CHECK( 0 == chunk.relativeAngularDistributionLocator(1) );
  CHECK( 8 == chunk.relativeAngularDistributionLocator(2) );
  CHECK( 41 == chunk.relativeAngularDistributionLocator(3) );

  CHECK( true == std::holds_alternative< IsotropicAngularDistribution >( chunk.angularDistributionData(1) ) );
  CHECK( true == std::holds_alternative< EquiprobableAngularBins >( chunk.angularDistributionData(2) ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistribution >( chunk.angularDistributionData(3) ) );
}
