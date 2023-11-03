// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/KalbachMannDistributionData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using KalbachMannDistributionData = continuous::KalbachMannDistributionData;
using TabulatedKalbachMannDistribution = continuous::TabulatedKalbachMannDistribution;

std::vector< double > chunk();
void verifyChunk( const KalbachMannDistributionData& );

SCENARIO( "KalbachMannDistributionData" ) {

  GIVEN( "valid data for a KalbachMannDistributionData instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< TabulatedKalbachMannDistribution > distributions  = {

        TabulatedKalbachMannDistribution(
            1.219437E+01, 1, { 0.000000E+00, 1.866919E-02 },
            { 5.356419E+01, 0.000000E+00 }, { 0., 1. }, { 0., 0. },
            { 2.391154E-01, 2.398743E-01 } ),
        TabulatedKalbachMannDistribution(
            20., 2, { 0.000000E+00, 1.120151E+00, 7.592137E+00 },
            { 7.738696E-02, 4.209016E-01, 1.226090E-11 },
            { 0.000000E+00, 5.382391E-01, 1.000000E+00 },
            { 2.491475E-03, 1.510768E-02, 9.775367E-01 },
            { 2.391154E-01, 2.847920E-01, 5.592013E-01 } )
      };
      std::size_t locb = 21;

      KalbachMannDistributionData chunk( std::move( distributions ), locb );

      THEN( "a KalbachMannDistributionData can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      KalbachMannDistributionData chunk( 21, xss.begin(), xss.end() );

      THEN( "a KalbachMannDistributionData can be constructed and "
            "members can be tested" ) {

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

  return {             0,             2,  1.219437E+01,  2.000000E+01,
                      27,            39,             1,             2,
            0.000000E+00,  1.866919E-02,  5.356419E+01,  0.000000E+00,
            0.000000E+00,  1.000000E+00,  0.000000E+00,  0.000000E+00,
            2.391154E-01,  2.398743E-01,             2,             3,
            0.000000E+00,  1.120151E+00,  7.592137E+00,  7.738696E-02,
            4.209016E-01,  1.226090E-11,  0.000000E+00,  5.382391E-01,
            1.000000E+00,  2.491475E-03,  1.510768E-02,  9.775367E-01,
            2.391154E-01,  2.847920E-01,  5.592013E-01 };}

void verifyChunk( const KalbachMannDistributionData& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 35 == chunk.length() );
  CHECK( "KalbachMannDistributionData" == chunk.name() );

  CHECK( EnergyDistributionType::KalbachMann == chunk.LAW() );
  CHECK( EnergyDistributionType::KalbachMann == chunk.type() );

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
  CHECK_THAT( 1.219437E+01, WithinRel( chunk.incidentEnergies()[0] ) );
  CHECK_THAT( 20., WithinRel( chunk.incidentEnergies()[1] ) );

  CHECK_THAT( 1.219437E+01, WithinRel( chunk.incidentEnergy(1) ) );
  CHECK_THAT( 20., WithinRel( chunk.incidentEnergy(2) ) );

  CHECK_THAT( 1.219437E+01, WithinRel( chunk.minimumIncidentEnergy() ) );
  CHECK_THAT( 20., WithinRel( chunk.maximumIncidentEnergy() ) );

  CHECK( 27 == chunk.LOCC(1) );
  CHECK( 39 == chunk.LOCC(2) );
  CHECK( 27 == chunk.distributionLocator(1) );
  CHECK( 39 == chunk.distributionLocator(2) );

  CHECK( 7 == chunk.relativeDistributionLocator(1) );
  CHECK( 19 == chunk.relativeDistributionLocator(2) );

  auto data1 = chunk.distribution(1);
  CHECK_THAT( 1.219437E+01, WithinRel( data1.incidentEnergy() ) );
  CHECK( 1 == data1.interpolation() );
  CHECK( 0 == data1.numberDiscretePhotonLines() );
  CHECK( 2 == data1.numberOutgoingEnergies() );

  CHECK( 2 == data1.outgoingEnergies().size() );
  CHECK_THAT( 0.0, WithinRel( data1.outgoingEnergies().front() ) );
  CHECK_THAT( 1.866919E-02, WithinRel( data1.outgoingEnergies().back() ) );

  CHECK( 2 == data1.pdf().size() );
  CHECK_THAT( 5.356419E+01, WithinRel( data1.pdf().front() ) );
  CHECK_THAT( 0., WithinRel( data1.pdf().back() ) );

  CHECK( 2 == data1.cdf().size() );
  CHECK_THAT( 0., WithinRel( data1.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data1.cdf().back() ) );

  CHECK( 2 == data1.precompoundFractionValues().size() );
  CHECK_THAT( 0., WithinRel( data1.precompoundFractionValues().front() ) );
  CHECK_THAT( 0., WithinRel( data1.precompoundFractionValues().back() ) );

  CHECK( 2 == data1.angularDistributionSlopeValues().size() );
  CHECK_THAT( 2.391154E-01, WithinRel( data1.angularDistributionSlopeValues().front() ) );
  CHECK_THAT( 2.398743E-01, WithinRel( data1.angularDistributionSlopeValues().back() ) );

  auto data2 = chunk.distribution(2);
  CHECK_THAT( 20., WithinRel( data2.incidentEnergy() ) );
  CHECK( 2 == data2.interpolation() );
  CHECK( 0 == data2.numberDiscretePhotonLines() );
  CHECK( 3 == data2.numberOutgoingEnergies() );

  CHECK( 3 == data2.outgoingEnergies().size() );
  CHECK_THAT( 0.0, WithinRel( data2.outgoingEnergies().front() ) );
  CHECK_THAT( 7.592137E+00, WithinRel( data2.outgoingEnergies().back() ) );

  CHECK( 3 == data2.pdf().size() );
  CHECK_THAT( 7.738696E-02, WithinRel( data2.pdf().front() ) );
  CHECK_THAT( 1.226090E-11, WithinRel( data2.pdf().back() ) );

  CHECK( 3 == data2.cdf().size() );
  CHECK_THAT( 0., WithinRel( data2.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data2.cdf().back() ) );

  CHECK( 3 == data2.precompoundFractionValues().size() );
  CHECK_THAT( 2.491475E-03, WithinRel( data2.precompoundFractionValues().front() ) );
  CHECK_THAT( 9.775367E-01, WithinRel( data2.precompoundFractionValues().back() ) );

  CHECK( 3 == data2.angularDistributionSlopeValues().size() );
  CHECK_THAT( 2.391154E-01, WithinRel( data2.angularDistributionSlopeValues().front() ) );
  CHECK_THAT( 5.592013E-01, WithinRel( data2.angularDistributionSlopeValues().back() ) );
}
