// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/MultiDistributionData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using MultiDistributionData = continuous::MultiDistributionData;
using DistributionProbability = continuous::DistributionProbability;
using DistributionData = MultiDistributionData::DistributionData;
using KalbachMannDistributionData = continuous::KalbachMannDistributionData;
using TabulatedKalbachMannDistribution = continuous::TabulatedKalbachMannDistribution;
using GeneralEvaporationSpectrum = continuous::GeneralEvaporationSpectrum;

std::vector< double > chunk();
void verifyChunk( const MultiDistributionData& );

SCENARIO( "MultiDistributionData" ) {

  GIVEN( "valid data for a MultiDistributionData instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< DistributionProbability > probabilities  = {

        DistributionProbability( { 1.219437E+01, 2.000000E+01 },
                                 { 2.500000E-01, 7.500000E-01 } ),
        DistributionProbability( { 1e-5, 2.000000E+01 },
                                 { 7.500000E-01, 2.500000E-01 } )
      };

      std::vector< DistributionData > distributions  = {

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
                { 2.391154E-01, 2.847920E-01, 5.592013E-01 } ) } ),
        GeneralEvaporationSpectrum(

          { 1e-5, 1., 10., 20. }, { 1., 2., 3., 4. }, { 5., 6., 7. } )
      };
      std::size_t locb = 12;

      MultiDistributionData chunk( std::move( probabilities ),
                                   std::move( distributions ), locb );

      THEN( "a MultiDistributionData can be constructed and "
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

      MultiDistributionData chunk( 12, xss.begin(), xss.end() );

      THEN( "a MultiDistributionData can be constructed and "
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

  return {  // LNW = 56, LAW = 44, IDAT = 21
                     56,                 44,            21,             0,
                      2,       1.219437E+01,  2.000000E+01,  2.500000E-01,
            7.500000E-01,
            // Kalbach-Mann spectrum
                       0,             2,  1.219437E+01,  2.000000E+01,
                      27,            39,             1,             2,
            0.000000E+00,  1.866919E-02,  5.356419E+01,  0.000000E+00,
            0.000000E+00,  1.000000E+00,  0.000000E+00,  0.000000E+00,
            2.391154E-01,  2.398743E-01,             2,             3,
            0.000000E+00,  1.120151E+00,  7.592137E+00,  7.738696E-02,
            4.209016E-01,  1.226090E-11,  0.000000E+00,  5.382391E-01,
            1.000000E+00,  2.491475E-03,  1.510768E-02,  9.775367E-01,
            2.391154E-01,  2.847920E-01,  5.592013E-01,
            // LNW = 0, LAW = 5, IDAT = 65
                      0,                  5,            65,             0,
                      2,               1e-5,  2.000000E+01,  7.500000E-01,
            2.500000E-01,
            // general evaporation spectrum
            0,
            4, 1e-5, 1., 10., 20., 1., 2., 3., 4.,
            3, 5., 6., 7. };
}

void verifyChunk( const MultiDistributionData& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 67 == chunk.length() );
  CHECK( "MultiDistributionData" == chunk.name() );

  CHECK( EnergyDistributionType::MultiDistribution == chunk.LAW() );
  CHECK( EnergyDistributionType::MultiDistribution == chunk.type() );

  CHECK( 2 == chunk.numberDistributions() );
  CHECK( 2 == chunk.probabilities().size() );
  CHECK( 2 == chunk.distributions().size() );

  auto probability1 = chunk.probability( 1 );
  CHECK( 0 == probability1.interpolationData().NB() );
  CHECK( 0 == probability1.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == probability1.interpolationData().INT().size() );
  CHECK( 0 == probability1.interpolationData().interpolants().size() );
  CHECK( 0 == probability1.interpolationData().NBT().size() );
  CHECK( 0 == probability1.interpolationData().boundaries().size() );

  CHECK( 0 == probability1.NB() );
  CHECK( 0 == probability1.numberInterpolationRegions() );
  CHECK( 0 == probability1.INT().size() );
  CHECK( 0 == probability1.interpolants().size() );
  CHECK( 0 == probability1.NBT().size() );
  CHECK( 0 == probability1.boundaries().size() );

  CHECK( 2 == probability1.NE() );
  CHECK( 2 == probability1.numberEnergyPoints() );

  CHECK( 2 == probability1.energies().size() );
  CHECK_THAT( 1.219437E+01, WithinRel( probability1.energies()[0] ) );
  CHECK_THAT( 20., WithinRel( probability1.energies()[1] ) );

  CHECK( 2 == probability1.probabilities().size() );
  CHECK_THAT( 0.25, WithinRel( probability1.probabilities()[0] ) );
  CHECK_THAT( 0.75, WithinRel( probability1.probabilities()[1] ) );

  auto probability2 = chunk.probability( 2 );
  CHECK( 0 == probability2.interpolationData().NB() );
  CHECK( 0 == probability2.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == probability2.interpolationData().INT().size() );
  CHECK( 0 == probability2.interpolationData().interpolants().size() );
  CHECK( 0 == probability2.interpolationData().NBT().size() );
  CHECK( 0 == probability2.interpolationData().boundaries().size() );

  CHECK( 0 == probability2.NB() );
  CHECK( 0 == probability2.numberInterpolationRegions() );
  CHECK( 0 == probability2.INT().size() );
  CHECK( 0 == probability2.interpolants().size() );
  CHECK( 0 == probability2.NBT().size() );
  CHECK( 0 == probability2.boundaries().size() );

  CHECK( 2 == probability2.NE() );
  CHECK( 2 == probability2.numberEnergyPoints() );

  CHECK( 2 == probability2.energies().size() );
  CHECK_THAT( 1e-5, WithinRel( probability2.energies()[0] ) );
  CHECK_THAT( 20., WithinRel( probability2.energies()[1] ) );

  CHECK( 2 == probability2.probabilities().size() );
  CHECK_THAT( 0.75, WithinRel( probability2.probabilities()[0] ) );
  CHECK_THAT( 0.25, WithinRel( probability2.probabilities()[1] ) );

  CHECK( true == std::holds_alternative< KalbachMannDistributionData >( chunk.distribution( 1 ) ) );
  CHECK( true == std::holds_alternative< GeneralEvaporationSpectrum >( chunk.distribution( 2 ) ) );
  CHECK( true == std::holds_alternative< KalbachMannDistributionData >( chunk.distributions()[0] ) );
  CHECK( true == std::holds_alternative< GeneralEvaporationSpectrum >( chunk.distributions()[1] ) );

  auto distribution1 = std::get< KalbachMannDistributionData >( chunk.distribution( 1 ) );
  CHECK( 0 == distribution1.interpolationData().NB() );
  CHECK( 0 == distribution1.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == distribution1.interpolationData().INT().size() );
  CHECK( 0 == distribution1.interpolationData().interpolants().size() );
  CHECK( 0 == distribution1.interpolationData().NBT().size() );
  CHECK( 0 == distribution1.interpolationData().boundaries().size() );

  CHECK( 0 == distribution1.NB() );
  CHECK( 0 == distribution1.numberInterpolationRegions() );
  CHECK( 0 == distribution1.INT().size() );
  CHECK( 0 == distribution1.interpolants().size() );
  CHECK( 0 == distribution1.NBT().size() );
  CHECK( 0 == distribution1.boundaries().size() );

  CHECK( 2 == distribution1.NE() );
  CHECK( 2 == distribution1.numberIncidentEnergies() );

  CHECK( 2 == distribution1.incidentEnergies().size() );
  CHECK_THAT( 1.219437E+01, WithinRel( distribution1.incidentEnergies()[0] ) );
  CHECK_THAT( 20., WithinRel( distribution1.incidentEnergies()[1] ) );

  CHECK_THAT( 1.219437E+01, WithinRel( distribution1.incidentEnergy(1) ) );
  CHECK_THAT( 20., WithinRel( distribution1.incidentEnergy(2) ) );

  CHECK_THAT( 1.219437E+01, WithinRel( distribution1.minimumIncidentEnergy() ) );
  CHECK_THAT( 20., WithinRel( distribution1.maximumIncidentEnergy() ) );

  CHECK( 27 == distribution1.LOCC(1) );
  CHECK( 39 == distribution1.LOCC(2) );
  CHECK( 27 == distribution1.distributionLocator(1) );
  CHECK( 39 == distribution1.distributionLocator(2) );

  CHECK( 7 == distribution1.relativeDistributionLocator(1) );
  CHECK( 19 == distribution1.relativeDistributionLocator(2) );

  auto data1 = distribution1.distribution(1);
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

  auto data2 = distribution1.distribution(2);
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

  auto distribution2 = std::get< GeneralEvaporationSpectrum >( chunk.distribution( 2 ) );
  CHECK( 0 == distribution2.interpolationData().NB() );
  CHECK( 0 == distribution2.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == distribution2.interpolationData().INT().size() );
  CHECK( 0 == distribution2.interpolationData().interpolants().size() );
  CHECK( 0 == distribution2.interpolationData().NBT().size() );
  CHECK( 0 == distribution2.interpolationData().boundaries().size() );

  CHECK( 0 == distribution2.NB() );
  CHECK( 0 == distribution2.numberInterpolationRegions() );
  CHECK( 0 == distribution2.INT().size() );
  CHECK( 0 == distribution2.interpolants().size() );
  CHECK( 0 == distribution2.NBT().size() );
  CHECK( 0 == distribution2.boundaries().size() );

  CHECK( 4 == distribution2.NE() );
  CHECK( 4 == distribution2.numberEnergyPoints() );

  CHECK( 4 == distribution2.energies().size() );
  CHECK_THAT( 1e-05, WithinRel( distribution2.energies()[0] ) );
  CHECK_THAT( 1., WithinRel( distribution2.energies()[1] ) );
  CHECK_THAT( 10., WithinRel( distribution2.energies()[2] ) );
  CHECK_THAT( 20., WithinRel( distribution2.energies()[3] ) );

  CHECK( 4 == distribution2.temperatures().size() );
  CHECK_THAT( 1., WithinRel( distribution2.temperatures()[0] ) );
  CHECK_THAT( 2., WithinRel( distribution2.temperatures()[1] ) );
  CHECK_THAT( 3., WithinRel( distribution2.temperatures()[2] ) );
  CHECK_THAT( 4., WithinRel( distribution2.temperatures()[3] ) );

  CHECK_THAT( 1e-5, WithinRel( distribution2.minimumIncidentEnergy() ) );
  CHECK_THAT( 20., WithinRel( distribution2.maximumIncidentEnergy() ) );

  CHECK( 3 == distribution2.NET() );
  CHECK( 2 == distribution2.numberBins() );

  CHECK( 3 == distribution2.bins().size() );
  CHECK_THAT( 5., WithinRel( distribution2.bins()[0] ) );
  CHECK_THAT( 6., WithinRel( distribution2.bins()[1] ) );
  CHECK_THAT( 7., WithinRel( distribution2.bins()[2] ) );
}
