// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/EnergyDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EnergyDistributionBlock = continuous::EnergyDistributionBlock;
using FrameAndMultiplicityBlock = continuous::FrameAndMultiplicityBlock;
using LevelScatteringDistribution = continuous::LevelScatteringDistribution;
using TabulatedKalbachMannDistribution = continuous::TabulatedKalbachMannDistribution;
using KalbachMannDistributionData = continuous::KalbachMannDistributionData;
using EnergyDistributionData = continuous::EnergyDistributionData;
using MultiplicityData = continuous::MultiplicityData;
using TabulatedMultiplicity = continuous::TabulatedMultiplicity;

std::vector< double > chunk();
void verifyChunk( const EnergyDistributionBlock& );

SCENARIO( "EnergyDistributionBlock" ) {

  GIVEN( "valid data for an EnergyDistributionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

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
      std::vector< MultiplicityData > multiplicities = {

        TabulatedMultiplicity( { 1e-11, 20. }, { 1., 1. } ),
        unsigned{ 1 }
      };
      std::vector< ReferenceFrame > frames = {

        ReferenceFrame::Laboratory, ReferenceFrame::CentreOfMass
      };

      EnergyDistributionBlock chunk( std::move( distributions ),
                                     std::move( multiplicities ),
                                     std::move( frames ) );

      THEN( "an EnergyDistributionBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators and the TYR block" ) {

      FrameAndMultiplicityBlock tyr( { ReferenceFrame::Laboratory,
                                       ReferenceFrame::CentreOfMass },
                                     { 101, 1 } );

      EnergyDistributionBlock chunk( xss.begin(), xss.begin() + 2, xss.end(),
                                     tyr, 2 );

      THEN( "an EnergyDistributionBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  // 2 reactions
  // the given data:
  //   - for reaction 1 : 1 law -> level scattering data, with energy dependent yield
  //   - for reaction 2 : 1 law -> Kalbach-Mann systematics for two incident energies
  return {
           // LDLW
                           7,                 18,
           // DLW - reaction 1 - energy dependent multiplicity
                           0,                  2,  1.00000000000E-11,  2.00000000000E+01,
           1.00000000000E+00,  1.00000000000E+00,
           // DLW - reaction 1 - LNW = 0, LAW = 3, IDAT = 16
                           0,                  3,                 16,                  0,
                           2,        2.249999e-3,  2.00000000000E+01,  1.00000000000E+00,
           1.00000000000E+00,  7.71295800000E-05,           .9914722,
           // DLW - reaction 2 - LNW = 0, LAW = 44, IDAT = 27
                           0,                 44,                 27,                  0,
                           2,       1.219437E+01,  2.00000000000E+01,  1.00000000000E+00,
           1.00000000000E+00,                  0,                  2,       1.219437E+01,
                2.000000E+01,                 33,                 45,                  1,
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
  CHECK( 63 == chunk.length() );
  CHECK( "DLW" == chunk.name() );

  CHECK( 2 == chunk.NR() );
  CHECK( 2 == chunk.numberReactions() );
  CHECK( 2 == chunk.data().size() );

  CHECK( 7 == chunk.LDLW(1) );
  CHECK( 18 == chunk.LDLW(2) );
  CHECK( 7 == chunk.energyDistributionLocator(1) );
  CHECK( 18 == chunk.energyDistributionLocator(2) );

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
  CHECK( 33 == data2.LOCC(1) );
  CHECK( 45 == data2.LOCC(2) );
  CHECK( 33 == data2.distributionLocator(1) );
  CHECK( 45 == data2.distributionLocator(2) );
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

  CHECK( ReferenceFrame::Laboratory == chunk.referenceFrame(1) );
  CHECK( ReferenceFrame::CentreOfMass == chunk.referenceFrame(2) );

  CHECK( true == std::holds_alternative< TabulatedMultiplicity >( chunk.multiplicityData(1) ) );
  CHECK( true == std::holds_alternative< unsigned int >( chunk.multiplicityData(2) ) );

  auto multiplicity1 = std::get< TabulatedMultiplicity >( chunk.multiplicityData(1) );
  CHECK( 0 == multiplicity1.interpolationData().NB() );
  CHECK( 0 == multiplicity1.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == multiplicity1.interpolationData().INT().size() );
  CHECK( 0 == multiplicity1.interpolationData().interpolants().size() );
  CHECK( 0 == multiplicity1.interpolationData().NBT().size() );
  CHECK( 0 == multiplicity1.interpolationData().boundaries().size() );

  CHECK( 0 == multiplicity1.NB() );
  CHECK( 0 == multiplicity1.numberInterpolationRegions() );
  CHECK( 0 == multiplicity1.INT().size() );
  CHECK( 0 == multiplicity1.interpolants().size() );
  CHECK( 0 == multiplicity1.NBT().size() );
  CHECK( 0 == multiplicity1.boundaries().size() );

  CHECK( 2 == multiplicity1.NE() );
  CHECK( 2 == multiplicity1.numberEnergyPoints() );

  CHECK( 2 == multiplicity1.energies().size() );
  CHECK_THAT( 1e-11, WithinRel( multiplicity1.energies()[0] ) );
  CHECK_THAT( 20., WithinRel( multiplicity1.energies()[1] ) );

  CHECK( 2 == multiplicity1.multiplicities().size() );
  CHECK_THAT( 1., WithinRel( multiplicity1.multiplicities()[0] ) );
  CHECK_THAT( 1., WithinRel( multiplicity1.multiplicities()[1] ) );

  auto multiplicity2 = std::get< unsigned int >( chunk.multiplicityData(2) );
  CHECK( 1 == multiplicity2 );

  decltype(auto) tyr = chunk.tyrMultiplicities();
  CHECK( 2 == tyr.size() );
  CHECK( 101 == tyr[0] );
  CHECK( 1 == tyr[1] );
}
