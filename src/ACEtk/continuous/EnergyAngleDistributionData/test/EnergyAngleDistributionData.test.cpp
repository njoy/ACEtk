// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/EnergyAngleDistributionData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EnergyAngleDistributionData = continuous::EnergyAngleDistributionData;
using TabulatedEnergyAngleDistribution = continuous::TabulatedEnergyAngleDistribution;
using TabulatedAngularDistributionWithProbability = continuous::TabulatedAngularDistributionWithProbability;

std::vector< double > chunk();
void verifyChunk( const EnergyAngleDistributionData&, const std::vector< double >& );
EnergyAngleDistributionData makeDummyBlock();

SCENARIO( "EnergyAngleDistributionData" ) {

  GIVEN( "valid data for an EnergyAngleDistributionData instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< TabulatedEnergyAngleDistribution > distributions  = {

        TabulatedEnergyAngleDistribution(
          1e-5, 2,
          { TabulatedAngularDistributionWithProbability(
              2.1, 0.5, 0.5, 2, { -1.0, 0.0, 1.0 }, { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ),
            TabulatedAngularDistributionWithProbability(
              20., 0.5, 1.0, 1, { -1.0, 1.0 }, { 0.5, 0.5 }, { 0.0, 1.0 } ) } ),
        TabulatedEnergyAngleDistribution(
          20., 2,
          { TabulatedAngularDistributionWithProbability(
              1.1, 0.5, 0.5, 1, { -1.0, 1.0 }, { 0.5, 0.5 }, { 0.0, 1.0 } ),
            TabulatedAngularDistributionWithProbability(
              15., 0.5, 1.0, 2, { -1.0, 0.0, 1.0 }, { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ) } )
      };
      std::size_t locb = 21;

      EnergyAngleDistributionData chunk( std::move( distributions ), locb );

      THEN( "an EnergyAngleDistributionData can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      EnergyAngleDistributionData chunk( 21, xss.begin(), xss.end() );

      THEN( "an EnergyAngleDistributionData can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { // incident energies: lin-lin interpolation, 2 values, 2 locators
                       0,             2,  1.000000E-05,  2.000000E+01,
                      27,            56,
           // distribution data for incident energy 1
                       2,             2,  2.100000E+00,  2.000000E+01,
            0.500000E+00,  0.500000E+00,  0.500000E+00,  1.000000E+00,
                      37,            48,             2,             3,
           -1.000000E+00,  0.000000E+00,  1.000000E+00,  0.500000E+00,
            0.500000E+00,  0.500000E+00,  0.000000E+00,  0.500000E+00,
            1.000000E+00,             1,             2, -1.000000E+00,
            1.000000E+00,  0.500000E+00,  0.500000E+00,  0.000000E+00,
            1.000000E+00,
           // distribution data for incident energy 2
                       2,             2,  1.100000E+00,  1.500000E+01,
            0.500000E+00,  0.500000E+00,  0.500000E+00,  1.000000E+00,
                      66,            74,             1,             2,
           -1.000000E+00,  1.000000E+00,  0.500000E+00,  0.500000E+00,
            0.000000E+00,  1.000000E+00,             2,             3,
           -1.000000E+00,  0.000000E+00,  1.000000E+00,  0.500000E+00,
            0.500000E+00,  0.500000E+00,  0.000000E+00,  0.500000E+00,
            1.000000E+00 };
}

void verifyChunk( const EnergyAngleDistributionData& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 64 == chunk.length() );
  CHECK( "EnergyAngleDistributionData" == chunk.name() );

  CHECK( EnergyDistributionType::TabulatedEnergyAngle == chunk.LAW() );
  CHECK( EnergyDistributionType::TabulatedEnergyAngle == chunk.type() );

  CHECK( 0 == chunk.interpolationData().NB() );
  CHECK( 0 == chunk.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == chunk.interpolationData().INT().size() );
  CHECK( 0 == chunk.interpolationData().interpolants().size() );
  CHECK( 0 == chunk.interpolationData().NBT().size() );
  CHECK( 0 == chunk.interpolationData().boundaries().size() );

  CHECK( 0 == chunk.NB() );
  CHECK( 0 == chunk.numberInterpolationRegions() );
  CHECK( 0 == chunk.INT().size() );
  CHECK( 0 == chunk.interpolants().size() );
  CHECK( 0 == chunk.NBT().size() );
  CHECK( 0 == chunk.boundaries().size() );

  CHECK( 2 == chunk.NE() );
  CHECK( 2 == chunk.numberIncidentEnergies() );

  CHECK( 2 == chunk.incidentEnergies().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergies()[0] ) );
  CHECK_THAT( 20., WithinRel( chunk.incidentEnergies()[1] ) );

  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergy(1) ) );
  CHECK_THAT( 20., WithinRel( chunk.incidentEnergy(2) ) );

  CHECK( 27 == chunk.LOCC(1) );
  CHECK( 56 == chunk.LOCC(2) );
  CHECK( 27 == chunk.distributionLocator(1) );
  CHECK( 56 == chunk.distributionLocator(2) );

  CHECK( 7 == chunk.relativeDistributionLocator(1) );
  CHECK( 36 == chunk.relativeDistributionLocator(2) );

  auto data1 = chunk.distribution(1);

  CHECK_THAT( 1e-5, WithinRel( data1.incidentEnergy() ) );

  CHECK( 2 == data1.interpolation() );

  CHECK( 2 == data1.NE() );
  CHECK( 2 == data1.numberOutgoingEnergies() );

  CHECK( 2 == data1.outgoingEnergies().size() );
  CHECK_THAT( 2.1, WithinRel( data1.outgoingEnergies()[0] ) );
  CHECK_THAT( 20., WithinRel( data1.outgoingEnergies()[1] ) );

  CHECK( 2 == data1.pdf().size() );
  CHECK_THAT( 0.5, WithinRel( data1.pdf()[0] ) );
  CHECK_THAT( 0.5, WithinRel( data1.pdf()[1] ) );

  CHECK( 2 == data1.cdf().size() );
  CHECK_THAT( 0.5, WithinRel( data1.cdf()[0] ) );
  CHECK_THAT( 1.0, WithinRel( data1.cdf()[1] ) );

  CHECK_THAT( 2.1, WithinRel( data1.outgoingEnergy(1) ) );
  CHECK_THAT( 20., WithinRel( data1.outgoingEnergy(2) ) );

  CHECK_THAT( 0.5, WithinRel( data1.probability(1) ) );
  CHECK_THAT( 0.5, WithinRel( data1.probability(2) ) );

  CHECK_THAT( 0.5, WithinRel( data1.cumulativeProbability(1) ) );
  CHECK_THAT( 1.0, WithinRel( data1.cumulativeProbability(2) ) );

  CHECK( 37 == data1.LOCC(1) );
  CHECK( 48 == data1.LOCC(2) );
  CHECK( 37 == data1.distributionLocator(1) );
  CHECK( 48 == data1.distributionLocator(2) );

  CHECK( 11 == data1.relativeDistributionLocator(1) );
  CHECK( 22 == data1.relativeDistributionLocator(2) );

  auto data11 = data1.distribution(1);
  CHECK_THAT( 2.1, WithinRel( data11.energy() ) );
  CHECK_THAT( 0.5, WithinRel( data11.probability() ) );
  CHECK_THAT( 0.5, WithinRel( data11.cumulativeProbability() ) );
  CHECK( 2 == data11.interpolation() );
  CHECK( 3 == data11.numberCosines() );

  CHECK( 3 == data11.cosines().size() );
  CHECK_THAT( -1., WithinRel( data11.cosines().front() ) );
  CHECK_THAT( +1., WithinRel( data11.cosines().back() ) );

  CHECK( 3 == data11.pdf().size() );
  CHECK_THAT( .5, WithinRel( data11.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( data11.pdf().back() ) );

  CHECK( 3 == data11.cdf().size() );
  CHECK_THAT( 0., WithinRel( data11.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data11.cdf().back() ) );

  auto data12 = data1.distribution(2);
  CHECK_THAT( 20, WithinRel( data12.energy() ) );
  CHECK_THAT( 0.5, WithinRel( data12.probability() ) );
  CHECK_THAT( 1.0, WithinRel( data12.cumulativeProbability() ) );
  CHECK( 1 == data12.interpolation() );
  CHECK( 2 == data12.numberCosines() );

  CHECK( 2 == data12.cosines().size() );
  CHECK_THAT( -1., WithinRel( data12.cosines().front() ) );
  CHECK_THAT( +1., WithinRel( data12.cosines().back() ) );

  CHECK( 2 == data12.pdf().size() );
  CHECK_THAT( .5, WithinRel( data12.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( data12.pdf().back() ) );

  CHECK( 2 == data12.cdf().size() );
  CHECK_THAT( 0., WithinRel( data12.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data12.cdf().back() ) );

  auto data2 = chunk.distribution(2);

  CHECK_THAT( 20., WithinRel( data2.incidentEnergy() ) );

  CHECK( 2 == data2.interpolation() );

  CHECK( 2 == data2.NE() );
  CHECK( 2 == data2.numberOutgoingEnergies() );

  CHECK( 2 == data2.outgoingEnergies().size() );
  CHECK_THAT( 1.1, WithinRel( data2.outgoingEnergies()[0] ) );
  CHECK_THAT( 15., WithinRel( data2.outgoingEnergies()[1] ) );

  CHECK( 2 == data2.pdf().size() );
  CHECK_THAT( 0.5, WithinRel( data2.pdf()[0] ) );
  CHECK_THAT( 0.5, WithinRel( data2.pdf()[1] ) );

  CHECK( 2 == data1.cdf().size() );
  CHECK_THAT( 0.5, WithinRel( data2.cdf()[0] ) );
  CHECK_THAT( 1.0, WithinRel( data2.cdf()[1] ) );

  CHECK_THAT( 1.1, WithinRel( data2.outgoingEnergy(1) ) );
  CHECK_THAT( 15., WithinRel( data2.outgoingEnergy(2) ) );

  CHECK_THAT( 0.5, WithinRel( data2.probability(1) ) );
  CHECK_THAT( 0.5, WithinRel( data2.probability(2) ) );

  CHECK_THAT( 0.5, WithinRel( data2.cumulativeProbability(1) ) );
  CHECK_THAT( 1.0, WithinRel( data2.cumulativeProbability(2) ) );

  CHECK( 66 == data2.LOCC(1) );
  CHECK( 74 == data2.LOCC(2) );
  CHECK( 66 == data2.distributionLocator(1) );
  CHECK( 74 == data2.distributionLocator(2) );

  CHECK( 11 == data2.relativeDistributionLocator(1) );
  CHECK( 19 == data2.relativeDistributionLocator(2) );

  auto data21 = data2.distribution(1);
  CHECK_THAT( 1.1, WithinRel( data21.energy() ) );
  CHECK_THAT( 0.5, WithinRel( data21.probability() ) );
  CHECK_THAT( 0.5, WithinRel( data21.cumulativeProbability() ) );
  CHECK( 1 == data21.interpolation() );
  CHECK( 2 == data21.numberCosines() );

  CHECK( 2 == data21.cosines().size() );
  CHECK_THAT( -1., WithinRel( data21.cosines().front() ) );
  CHECK_THAT( +1., WithinRel( data21.cosines().back() ) );

  CHECK( 2 == data21.pdf().size() );
  CHECK_THAT( .5, WithinRel( data21.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( data21.pdf().back() ) );

  CHECK( 2 == data21.cdf().size() );
  CHECK_THAT( 0., WithinRel( data21.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data21.cdf().back() ) );

  auto data22 = data2.distribution(2);
  CHECK_THAT( 15, WithinRel( data22.energy() ) );
  CHECK_THAT( 0.5, WithinRel( data22.probability() ) );
  CHECK_THAT( 1.0, WithinRel( data22.cumulativeProbability() ) );
  CHECK( 2 == data22.interpolation() );
  CHECK( 3 == data22.numberCosines() );

  CHECK( 3 == data22.cosines().size() );
  CHECK_THAT( -1., WithinRel( data22.cosines().front() ) );
  CHECK_THAT( +1., WithinRel( data22.cosines().back() ) );

  CHECK( 3 == data22.pdf().size() );
  CHECK_THAT( .5, WithinRel( data22.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( data22.pdf().back() ) );

  CHECK( 3 == data22.cdf().size() );
  CHECK_THAT( 0., WithinRel( data22.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data22.cdf().back() ) );
}
