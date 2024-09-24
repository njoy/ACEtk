// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/SecondaryParticleEnergyDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using SecondaryParticleEnergyDistributionBlock = continuous::SecondaryParticleEnergyDistributionBlock;
using LevelScatteringDistribution = continuous::LevelScatteringDistribution;
using TabulatedKalbachMannDistribution = continuous::TabulatedKalbachMannDistribution;
using KalbachMannDistributionData = continuous::KalbachMannDistributionData;
using EnergyDistributionData = continuous::EnergyDistributionData;
using FrameAndMultiplicityBlock = continuous::FrameAndMultiplicityBlock;

std::vector< double > chunk();
void verifyChunk( const SecondaryParticleEnergyDistributionBlock&, const std::vector< double >& );
SecondaryParticleEnergyDistributionBlock makeDummyBlock();

SCENARIO( "SecondaryParticleEnergyDistributionBlock" ) {

  GIVEN( "valid data for an SecondaryParticleEnergyDistributionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly for a DLWH" ) {

      std::vector< EnergyDistributionData > distributions = {

        LevelScatteringDistribution( 2.249999e-3, 20.,
                                     7.71295800000E-05, .9914722 ),
        KalbachMannDistributionData(
          { TabulatedKalbachMannDistribution(
              1.219437E+01, 1, { 0.000000E+00, 1.866919E-02 },
              { 5.356419E+01, 0.000000E+00 }, { 0., 1. }, { 0., 0. },
              { 2.391154E-01, 2.398743E-01 } ),
            TabulatedKalbachMannDistribution(
              20., 2, { 0.000000E+00, 1.120151E+00, 7.592137E+00 },
              { 7.738696E-02, 4.209016E-01, 1.226090E-11 },
              { 0.000000E+00, 5.382391E-01, 1.000000E+00 },
              { 2.491475E-03, 1.510768E-02, 9.775367E-01 },
              { 2.391154E-01, 2.847920E-01, 5.592013E-01 } ) } )
      };
      std::vector< ReferenceFrame > frames = {

        ReferenceFrame::Laboratory, ReferenceFrame::CentreOfMass
      };

      SecondaryParticleEnergyDistributionBlock chunk( std::move( distributions ),
                                                      std::move( frames ) );

      THEN( "an SecondaryParticleEnergyDistributionBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators and the TYRH" ) {

      FrameAndMultiplicityBlock tyrh( { ReferenceFrame::Laboratory,
                                        ReferenceFrame::CentreOfMass } );

      SecondaryParticleEnergyDistributionBlock chunk( xss.begin(), xss.begin() + 2,
                                                      xss.end(), tyrh, 2 );

      THEN( "an SecondaryParticleEnergyDistributionBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      FrameAndMultiplicityBlock tyrh( { ReferenceFrame::Laboratory,
                                        ReferenceFrame::CentreOfMass } );

      SecondaryParticleEnergyDistributionBlock chunk( xss.begin(), xss.begin() + 2,
                                                      xss.end(), tyrh, 2 );
      SecondaryParticleEnergyDistributionBlock copy( chunk );

      THEN( "an SecondaryParticleEnergyDistributionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      FrameAndMultiplicityBlock tyrh( { ReferenceFrame::Laboratory,
                                        ReferenceFrame::CentreOfMass } );

      SecondaryParticleEnergyDistributionBlock chunk( xss.begin(), xss.begin() + 2,
                                                      xss.end(), tyrh, 2 );
      SecondaryParticleEnergyDistributionBlock move( std::move( chunk ) );

      THEN( "an SecondaryParticleEnergyDistributionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      FrameAndMultiplicityBlock tyrh( { ReferenceFrame::Laboratory,
                                        ReferenceFrame::CentreOfMass } );

      SecondaryParticleEnergyDistributionBlock chunk( xss.begin(), xss.begin() + 2,
                                                      xss.end(), tyrh, 2 );
      SecondaryParticleEnergyDistributionBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an SecondaryParticleEnergyDistributionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      FrameAndMultiplicityBlock tyrh( { ReferenceFrame::Laboratory,
                                        ReferenceFrame::CentreOfMass } );

      SecondaryParticleEnergyDistributionBlock chunk( xss.begin(), xss.begin() + 2,
                                                      xss.end(), tyrh, 2 );
      SecondaryParticleEnergyDistributionBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an SecondaryParticleEnergyDistributionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
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
           // LDLWH
                           1,                 12,
           // DLWH - reaction 1 - LNW = 0, LAW = 3, IDAT = 10
                           0,                  3,                 10,                  0,
                           2,        2.249999e-3,  2.00000000000E+01,  1.00000000000E+00,
           1.00000000000E+00,  7.71295800000E-05,           .9914722,
           // DLWH - reaction 2 - LNW = 0, LAW = 44, IDAT = 21
                           0,                 44,                 21,                  0,
                           2,       1.219437E+01,  2.00000000000E+01,  1.00000000000E+00,
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

void verifyChunk( const SecondaryParticleEnergyDistributionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 57 == chunk.length() );
  CHECK( "DLWH" == chunk.name() );

  CHECK( 2 == chunk.NR() );
  CHECK( 2 == chunk.numberReactions() );
  CHECK( 2 == chunk.data().size() );

  CHECK( 1 == chunk.LDLW(1) );
  CHECK( 12 == chunk.LDLW(2) );
  CHECK( 1 == chunk.energyDistributionLocator(1) );
  CHECK( 12 == chunk.energyDistributionLocator(2) );

  CHECK( true == std::holds_alternative< LevelScatteringDistribution >( chunk.energyDistributionData(1) ) );
  CHECK( true == std::holds_alternative< KalbachMannDistributionData >( chunk.energyDistributionData(2) ) );

  CHECK( true == std::holds_alternative< LevelScatteringDistribution >( chunk.data()[0] ) );
  CHECK( true == std::holds_alternative< KalbachMannDistributionData >( chunk.data()[1] ) );

  auto data1 = std::get< LevelScatteringDistribution >( chunk.energyDistributionData(1) );
  CHECK( EnergyDistributionType::LevelScattering == data1.LAW() );
  CHECK( EnergyDistributionType::LevelScattering == data1.type() );
  CHECK_THAT( 2.249999e-3, WithinRel( data1.minimumIncidentEnergy() ) );
  CHECK_THAT( 20., WithinRel( data1.maximumIncidentEnergy() ) );
  CHECK_THAT( 7.71295800000E-05, WithinRel( data1.C1() ) );
  CHECK_THAT( .9914722, WithinRel( data1.C2() ) );

  auto data2 = std::get< KalbachMannDistributionData >( chunk.energyDistributionData(2) );
  CHECK( EnergyDistributionType::KalbachMann == data2.LAW() );
  CHECK( EnergyDistributionType::KalbachMann == data2.type() );
  CHECK( 2 == data2.NE() );
  CHECK( 2 == data2.numberIncidentEnergies() );
  CHECK( 2 == data2.incidentEnergies().size() );
  CHECK_THAT( 1.219437E+01, WithinRel( data2.incidentEnergies()[0] ) );
  CHECK_THAT( 20., WithinRel( data2.incidentEnergies()[1] ) );
  CHECK_THAT( 1.219437E+01, WithinRel( data2.incidentEnergy(1) ) );
  CHECK_THAT( 20., WithinRel( data2.incidentEnergy(2) ) );
  CHECK_THAT( 1.219437E+01, WithinRel( data2.minimumIncidentEnergy() ) );
  CHECK_THAT( 20., WithinRel( data2.maximumIncidentEnergy() ) );
  CHECK( 27 == data2.LOCC(1) );
  CHECK( 39 == data2.LOCC(2) );
  CHECK( 27 == data2.distributionLocator(1) );
  CHECK( 39 == data2.distributionLocator(2) );
  CHECK( 7 == data2.relativeDistributionLocator(1) );
  CHECK( 19 == data2.relativeDistributionLocator(2) );
  auto data21 = data2.distribution(1);
  CHECK_THAT( 1.219437E+01, WithinRel( data21.incidentEnergy() ) );
  CHECK( 1 == data21.interpolation() );
  CHECK( 0 == data21.numberDiscretePhotonLines() );
  CHECK( 2 == data21.numberOutgoingEnergies() );
  CHECK( 2 == data21.outgoingEnergies().size() );
  CHECK_THAT( 0.0, WithinRel( data21.outgoingEnergies().front() ) );
  CHECK_THAT( 1.866919E-02, WithinRel( data21.outgoingEnergies().back() ) );
  CHECK( 2 == data21.pdf().size() );
  CHECK_THAT( 5.356419E+01, WithinRel( data21.pdf().front() ) );
  CHECK_THAT( 0., WithinRel( data21.pdf().back() ) );
  CHECK( 2 == data21.cdf().size() );
  CHECK_THAT( 0., WithinRel( data21.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data21.cdf().back() ) );
  CHECK( 2 == data21.precompoundFractionValues().size() );
  CHECK_THAT( 0., WithinRel( data21.precompoundFractionValues().front() ) );
  CHECK_THAT( 0., WithinRel( data21.precompoundFractionValues().back() ) );
  CHECK( 2 == data21.angularDistributionSlopeValues().size() );
  CHECK_THAT( 2.391154E-01, WithinRel( data21.angularDistributionSlopeValues().front() ) );
  CHECK_THAT( 2.398743E-01, WithinRel( data21.angularDistributionSlopeValues().back() ) );
  auto data22 = data2.distribution(2);
  CHECK_THAT( 20., WithinRel( data22.incidentEnergy() ) );
  CHECK( 2 == data22.interpolation() );
  CHECK( 0 == data22.numberDiscretePhotonLines() );
  CHECK( 3 == data22.numberOutgoingEnergies() );
  CHECK( 3 == data22.outgoingEnergies().size() );
  CHECK_THAT( 0.0, WithinRel( data22.outgoingEnergies().front() ) );
  CHECK_THAT( 7.592137E+00, WithinRel( data22.outgoingEnergies().back() ) );
  CHECK( 3 == data22.pdf().size() );
  CHECK_THAT( 7.738696E-02, WithinRel( data22.pdf().front() ) );
  CHECK_THAT( 1.226090E-11, WithinRel( data22.pdf().back() ) );
  CHECK( 3 == data22.cdf().size() );
  CHECK_THAT( 0., WithinRel( data22.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data22.cdf().back() ) );
  CHECK( 3 == data22.precompoundFractionValues().size() );
  CHECK_THAT( 2.491475E-03, WithinRel( data22.precompoundFractionValues().front() ) );
  CHECK_THAT( 9.775367E-01, WithinRel( data22.precompoundFractionValues().back() ) );
  CHECK( 3 == data22.angularDistributionSlopeValues().size() );
  CHECK_THAT( 2.391154E-01, WithinRel( data22.angularDistributionSlopeValues().front() ) );
  CHECK_THAT( 5.592013E-01, WithinRel( data22.angularDistributionSlopeValues().back() ) );

  CHECK( ReferenceFrame::Laboratory == chunk.referenceFrame(1).value() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.referenceFrame(2).value() );
}

SecondaryParticleEnergyDistributionBlock makeDummyBlock() {

  return { { LevelScatteringDistribution( 1., 2., 3., 4. ) },
           { ReferenceFrame::CentreOfMass } };
}
