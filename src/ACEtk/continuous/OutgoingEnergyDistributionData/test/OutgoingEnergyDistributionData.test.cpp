// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/OutgoingEnergyDistributionData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using OutgoingEnergyDistributionData = continuous::OutgoingEnergyDistributionData;
using TabulatedEnergyDistribution = continuous::TabulatedEnergyDistribution;

std::vector< double > chunk();
void verifyChunk( const OutgoingEnergyDistributionData&, const std::vector< double >& );
OutgoingEnergyDistributionData makeDummyBlock();

SCENARIO( "OutgoingEnergyDistributionData" ) {

  GIVEN( "valid data for an OutgoingEnergyDistributionData instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< TabulatedEnergyDistribution > distributions  = {

        TabulatedEnergyDistribution(
            1e-11, 2, { 0.0, .31, 1.84 },
            { 2.364290E-01, 1.050191E+00, 0. }, { 0., 4.932501E-01, 1. } ),
        TabulatedEnergyDistribution(
            20., 2, { 0.0, 1.84 }, { .5, .5 }, { 0., 1. } )
      };
      std::size_t locb = 21;

      OutgoingEnergyDistributionData chunk( std::move( distributions ), locb );

      THEN( "an OutgoingEnergyDistributionData can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      OutgoingEnergyDistributionData chunk( 21, xss.begin(), xss.end() );

      THEN( "an OutgoingEnergyDistributionData can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {             0,             2,  1.000000E-11,  2.000000E+01,
                      27,            38,             2,             3,
            0.000000E+00,  3.100000E-01,  1.840000E+00,  2.364290E-01,
            1.050191E+00,  0.000000E+00,  0.000000E+00,  4.932501E-01,
            1.000000E+00,             2,             2,  0.000000E+00,
            1.840000E+00,  5.000000E-01,  5.000000E-01,  0.000000E+00,
            1.000000E+00 };
}

void verifyChunk( const OutgoingEnergyDistributionData& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 25 == chunk.length() );
  CHECK( "OutgoingEnergyDistributionData" == chunk.name() );

  CHECK( EnergyDistributionType::TabulatedEnergy == chunk.LAW() );
  CHECK( EnergyDistributionType::TabulatedEnergy == chunk.type() );

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
  CHECK_THAT( 1e-11, WithinRel( chunk.incidentEnergies()[0] ) );
  CHECK_THAT( 20., WithinRel( chunk.incidentEnergies()[1] ) );

  CHECK_THAT( 1e-11, WithinRel( chunk.incidentEnergy(1) ) );
  CHECK_THAT( 20., WithinRel( chunk.incidentEnergy(2) ) );

  CHECK_THAT( 1e-11, WithinRel( chunk.minimumIncidentEnergy() ) );
  CHECK_THAT( 20., WithinRel( chunk.maximumIncidentEnergy() ) );

  CHECK( 27 == chunk.LOCC(1) );
  CHECK( 38 == chunk.LOCC(2) );
  CHECK( 27 == chunk.distributionLocator(1) );
  CHECK( 38 == chunk.distributionLocator(2) );

  CHECK( 7 == chunk.relativeDistributionLocator(1) );
  CHECK( 18 == chunk.relativeDistributionLocator(2) );

  auto data1 = chunk.distribution(1);
  CHECK_THAT( 1e-11, WithinRel( data1.energyOrCosine() ) );
  CHECK( 2 == data1.interpolation() );
  CHECK( 0 == data1.numberDiscretePhotonLines() );
  CHECK( 3 == data1.numberOutgoingEnergies() );

  CHECK( 3 == data1.outgoingEnergies().size() );
  CHECK_THAT( 0.0, WithinRel( data1.outgoingEnergies().front() ) );
  CHECK_THAT( 1.84, WithinRel( data1.outgoingEnergies().back() ) );

  CHECK( 3 == data1.pdf().size() );
  CHECK_THAT( 2.364290E-01, WithinRel( data1.pdf().front() ) );
  CHECK_THAT( 0., WithinRel( data1.pdf().back() ) );

  CHECK( 3 == data1.cdf().size() );
  CHECK_THAT( 0., WithinRel( data1.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data1.cdf().back() ) );

  auto data2 = chunk.distribution(2);
  CHECK_THAT( 20., WithinRel( data2.energyOrCosine() ) );
  CHECK( 2 == data2.interpolation() );
  CHECK( 0 == data2.numberDiscretePhotonLines() );
  CHECK( 2 == data2.numberOutgoingEnergies() );

  CHECK( 2 == data2.outgoingEnergies().size() );
  CHECK_THAT( 0.0, WithinRel( data2.outgoingEnergies().front() ) );
  CHECK_THAT( 1.84, WithinRel( data2.outgoingEnergies().back() ) );

  CHECK( 2 == data2.pdf().size() );
  CHECK_THAT( 0.5, WithinRel( data2.pdf().front() ) );
  CHECK_THAT( 0.5, WithinRel( data2.pdf().back() ) );

  CHECK( 2 == data2.cdf().size() );
  CHECK_THAT( 0., WithinRel( data2.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data2.cdf().back() ) );
}
