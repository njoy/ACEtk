// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/AngularDistributionData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using AngularDistributionData = continuous::AngularDistributionData;
using IsotropicAngularDistribution = continuous::IsotropicAngularDistribution;
using EquiprobableAngularBins = continuous::EquiprobableAngularBins;
using TabulatedAngularDistribution = continuous::TabulatedAngularDistribution;
using Distribution = AngularDistributionData::Distribution;

std::vector< double > chunk();
void verifyChunk( const AngularDistributionData&, const std::vector< double >& );
AngularDistributionData makeDummyBlock();

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

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      AngularDistributionData chunk( 6, xss.begin(), xss.end() );

      THEN( "an AngularDistributionData can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      AngularDistributionData chunk( 6, xss.begin(), xss.end() );
      AngularDistributionData copy( chunk );

      THEN( "a AngularDistributionData can be constructed and members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      AngularDistributionData chunk( 6, xss.begin(), xss.end() );
      AngularDistributionData move( std::move( chunk ) );

      THEN( "a AngularDistributionData can be constructed and members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      AngularDistributionData chunk( 6, xss.begin(), xss.end() );
      AngularDistributionData copy = makeDummyBlock();
      copy = chunk;

      THEN( "a AngularDistributionBlock can be constructed and members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      AngularDistributionData chunk( 6, xss.begin(), xss.end() );
      AngularDistributionData move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "a AngularDistributionBlock can be constructed and members can be tested" ) {

        verifyChunk( move, xss );
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

void verifyChunk( const AngularDistributionData& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 51 == chunk.length() );
  CHECK( "AngularDistributionData" == chunk.name() );

  CHECK( 3 == chunk.NE() );
  CHECK( 3 == chunk.numberIncidentEnergies() );
  CHECK( 3 == chunk.distributions().size() );

  CHECK( 3 == chunk.incidentEnergies().size() );
  CHECK_THAT( 1e-11, WithinRel( chunk.incidentEnergies()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.incidentEnergies()[1] ) );
  CHECK_THAT( 20., WithinRel( chunk.incidentEnergies()[2] ) );

  CHECK_THAT( 1e-11, WithinRel( chunk.incidentEnergy(1) ) );
  CHECK_THAT( 1., WithinRel( chunk.incidentEnergy(2) ) );
  CHECK_THAT( 20., WithinRel( chunk.incidentEnergy(3) ) );

  CHECK( 0 == chunk.LOCC(1) );
  CHECK( 13 == chunk.LOCC(2) );
  CHECK( -46 == chunk.LOCC(3) );
  CHECK( 0 == chunk.distributionLocator(1) );
  CHECK( 13 == chunk.distributionLocator(2) );
  CHECK( -46 == chunk.distributionLocator(3) );

  CHECK( AngularDistributionType::Isotropic == chunk.distributionType(1) );
  CHECK( AngularDistributionType::Equiprobable == chunk.distributionType(2) );
  CHECK( AngularDistributionType::Tabulated == chunk.distributionType(3) );
  CHECK( 0 == chunk.relativeDistributionLocator(1) );
  CHECK( 8 == chunk.relativeDistributionLocator(2) );
  CHECK( 41 == chunk.relativeDistributionLocator(3) );

  CHECK( true == std::holds_alternative< IsotropicAngularDistribution >( chunk.distribution(1) ) );
  CHECK( true == std::holds_alternative< EquiprobableAngularBins >( chunk.distribution(2) ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistribution >( chunk.distribution(3) ) );

  CHECK( true == std::holds_alternative< IsotropicAngularDistribution >( chunk.distributions()[0] ) );
  CHECK( true == std::holds_alternative< EquiprobableAngularBins >( chunk.distributions()[1] ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistribution >( chunk.distributions()[2] ) );
}

AngularDistributionData makeDummyBlock() {

  std::vector< Distribution > distributions = {

    TabulatedAngularDistribution(  1., 2, { -1.0, 1.0 }, { 0.5, 0.5 }, { 0.0, 1.0 } ),
    TabulatedAngularDistribution( 20., 2, { -1.0, 1.0 }, { 0.5, 0.5 }, { 0.0, 1.0 } )
  };
  std::size_t locb = 6;

  return { std::move( distributions ), locb };
}
