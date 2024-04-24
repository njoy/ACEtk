// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/AngleEnergyDistributionData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using AngleEnergyDistributionData = continuous::AngleEnergyDistributionData;
using TabulatedAngleEnergyDistribution = continuous::TabulatedAngleEnergyDistribution;
using TabulatedEnergyDistribution = continuous::TabulatedEnergyDistribution;

std::vector< double > chunk();
void verifyChunk( const AngleEnergyDistributionData& );

SCENARIO( "AngleEnergyDistributionData" ) {

  GIVEN( "valid data for an AngleEnergyDistributionData instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< TabulatedAngleEnergyDistribution > distributions  = {

        TabulatedAngleEnergyDistribution(
          1e-5, 2,
          { TabulatedEnergyDistribution(
              -1., 2, { 1e-5, 1.0, 20.0 }, { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ),
            TabulatedEnergyDistribution(
              1., 1, { 1e-3, 15.0 }, { 0.5, 0.5 }, { 0.0, 1.0 } ) } ),
        TabulatedAngleEnergyDistribution(
          20., 2,
          { TabulatedEnergyDistribution(
              -0.9, 1, { 1e-4, 12.0 }, { 0.5, 0.5 }, { 0.0, 1.0 } ),
            TabulatedEnergyDistribution(
              0.9, 2, { 1e-2, 2.0, 18.0 }, { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ) } )
      };
      std::size_t locb = 21;

      AngleEnergyDistributionData chunk( std::move( distributions ), locb );

      THEN( "an AngleEnergyDistributionData can be constructed and "
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

      AngleEnergyDistributionData chunk( 21, xss.begin(), xss.end() );

      THEN( "an AngleEnergyDistributionData can be constructed and "
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

  return { // incident energies: lin-lin interpolation, 2 values, 2 locators
                       0,             2,  1.000000E-05,  2.000000E+01,
                      27,            52,
           // distribution data for incident energy 1
                       2,             2, -1.000000E+00,  1.000000E+00,
                      33,            44,             2,             3,
            1.000000E-05,  1.000000E+00,  2.000000E+01,  0.500000E+00,
            0.500000E+00,  0.500000E+00,  0.000000E+00,  0.500000E+00,
            1.000000E+00,             1,             2,  1.000000E-03,
            1.500000E+01,  0.500000E+00,  0.500000E+00,  0.000000E+00,
            1.000000E+00,
           // distribution data for incident energy 2
                       2,             2, -9.000000E-01,  9.000000E-01,
                      58,            66,             1,             2,
            1.000000E-04,  1.200000E+01,  0.500000E+00,  0.500000E+00,
            0.000000E+00,  1.000000E+00,             2,             3,
            1.000000E-02,  2.000000E+00,  1.800000E+01,  0.500000E+00,
            0.500000E+00,  0.500000E+00,  0.000000E+00,  0.500000E+00,
            1.000000E+00 };
}

void verifyChunk( const AngleEnergyDistributionData& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 56 == chunk.length() );
  CHECK( "AngleEnergyDistributionData" == chunk.name() );

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
  CHECK( 2 == chunk.distributions().size() );

  CHECK( 2 == chunk.incidentEnergies().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergies()[0] ) );
  CHECK_THAT( 20., WithinRel( chunk.incidentEnergies()[1] ) );

  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergy(1) ) );
  CHECK_THAT( 20., WithinRel( chunk.incidentEnergy(2) ) );

  CHECK( 27 == chunk.LOCC(1) );
  CHECK( 52 == chunk.LOCC(2) );
  CHECK( 27 == chunk.distributionLocator(1) );
  CHECK( 52 == chunk.distributionLocator(2) );

  CHECK( 7 == chunk.relativeDistributionLocator(1) );
  CHECK( 32 == chunk.relativeDistributionLocator(2) );

  auto data1 = chunk.distribution(1);

  CHECK_THAT( 1e-5, WithinRel( data1.incidentEnergy() ) );

  CHECK( 2 == data1.interpolation() );

  CHECK( 2 == data1.NC() );
  CHECK( 2 == data1.numberCosines() );

  CHECK( 2 == data1.cosines().size() );
  CHECK_THAT( -1., WithinRel( data1.cosines()[0] ) );
  CHECK_THAT( 1., WithinRel( data1.cosines()[1] ) );

  CHECK_THAT( -1, WithinRel( data1.cosine(1) ) );
  CHECK_THAT( 1., WithinRel( data1.cosine(2) ) );

  CHECK( 33 == data1.LOCC(1) );
  CHECK( 44 == data1.LOCC(2) );
  CHECK( 33 == data1.distributionLocator(1) );
  CHECK( 44 == data1.distributionLocator(2) );

  CHECK( 7 == data1.relativeDistributionLocator(1) );
  CHECK( 18 == data1.relativeDistributionLocator(2) );

  auto data11 = data1.distribution(1);
  CHECK_THAT( -1., WithinRel( data11.energyOrCosine() ) );
  CHECK( 2 == data11.interpolation() );
  CHECK( 3 == data11.numberOutgoingEnergies() );

  CHECK( 3 == data11.outgoingEnergies().size() );
  CHECK_THAT( 1e-5, WithinRel( data11.outgoingEnergies().front() ) );
  CHECK_THAT( 20., WithinRel( data11.outgoingEnergies().back() ) );

  CHECK( 3 == data11.pdf().size() );
  CHECK_THAT( .5, WithinRel( data11.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( data11.pdf().back() ) );

  CHECK( 3 == data11.cdf().size() );
  CHECK_THAT( 0., WithinRel( data11.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data11.cdf().back() ) );

  auto data12 = data1.distribution(2);
  CHECK_THAT( 1., WithinRel( data12.energyOrCosine() ) );
  CHECK( 1 == data12.interpolation() );
  CHECK( 2 == data12.numberOutgoingEnergies() );

  CHECK( 2 == data12.outgoingEnergies().size() );
  CHECK_THAT( 1e-3, WithinRel( data12.outgoingEnergies().front() ) );
  CHECK_THAT( 15., WithinRel( data12.outgoingEnergies().back() ) );

  CHECK( 2 == data12.pdf().size() );
  CHECK_THAT( .5, WithinRel( data12.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( data12.pdf().back() ) );

  CHECK( 2 == data12.cdf().size() );
  CHECK_THAT( 0., WithinRel( data12.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data12.cdf().back() ) );

  auto data2 = chunk.distribution(2);

  CHECK_THAT( 20., WithinRel( data2.incidentEnergy() ) );

  CHECK( 2 == data2.interpolation() );

  CHECK( 2 == data2.NC() );
  CHECK( 2 == data2.numberCosines() );

  CHECK( 2 == data2.cosines().size() );
  CHECK_THAT( -0.9, WithinRel( data2.cosines()[0] ) );
  CHECK_THAT( 0.9, WithinRel( data2.cosines()[1] ) );

  CHECK_THAT( -0.9, WithinRel( data2.cosine(1) ) );
  CHECK_THAT( 0.9, WithinRel( data2.cosine(2) ) );

  CHECK( 58 == data2.LOCC(1) );
  CHECK( 66 == data2.LOCC(2) );
  CHECK( 58 == data2.distributionLocator(1) );
  CHECK( 66 == data2.distributionLocator(2) );

  CHECK( 7 == data2.relativeDistributionLocator(1) );
  CHECK( 15 == data2.relativeDistributionLocator(2) );

  auto data21 = data2.distribution(1);
  CHECK_THAT( -0.9, WithinRel( data21.energyOrCosine() ) );
  CHECK( 1 == data21.interpolation() );
  CHECK( 2 == data21.numberOutgoingEnergies() );

  CHECK( 2 == data21.outgoingEnergies().size() );
  CHECK_THAT( 1e-4, WithinRel( data21.outgoingEnergies().front() ) );
  CHECK_THAT( 12., WithinRel( data21.outgoingEnergies().back() ) );

  CHECK( 2 == data21.pdf().size() );
  CHECK_THAT( .5, WithinRel( data21.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( data21.pdf().back() ) );

  CHECK( 2 == data21.cdf().size() );
  CHECK_THAT( 0., WithinRel( data21.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data21.cdf().back() ) );

  auto data22 = data2.distribution(2);
  CHECK_THAT( 0.9, WithinRel( data22.energyOrCosine() ) );
  CHECK( 2 == data22.interpolation() );
  CHECK( 3 == data22.numberOutgoingEnergies() );

  CHECK( 3 == data22.outgoingEnergies().size() );
  CHECK_THAT( 1e-2, WithinRel( data22.outgoingEnergies().front() ) );
  CHECK_THAT( 18., WithinRel( data22.outgoingEnergies().back() ) );

  CHECK( 3 == data22.pdf().size() );
  CHECK_THAT( .5, WithinRel( data22.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( data22.pdf().back() ) );

  CHECK( 3 == data22.cdf().size() );
  CHECK_THAT( 0., WithinRel( data22.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data22.cdf().back() ) );
}
