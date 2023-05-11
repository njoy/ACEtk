#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/MultiEvaporationSpectrum.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using MultiEvaporationSpectrum = block::MultiEvaporationSpectrum;
using DistributionProbability = block::DistributionProbability;
using EvaporationSpectrum = block::EvaporationSpectrum;

std::vector< double > chunk();
void verifyChunk( const MultiEvaporationSpectrum& );

SCENARIO( "MultiEvaporationSpectrum" ) {

  GIVEN( "valid data for a MultiEvaporationSpectrum instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< DistributionProbability > probabilities  = {

        DistributionProbability( { 1e-5, 2.000000E+01 },
                                 { 2.500000E-01, 7.500000E-01 } ),
        DistributionProbability( { 1e-5, 2.000000E+01 },
                                 { 7.500000E-01, 2.500000E-01 } )
      };

      std::vector< EvaporationSpectrum > distributions  = {

        EvaporationSpectrum( { 1e-5, 2., 5., 20. }, { 5., 6., 7., 8. }, 1.5e+6 ),
        EvaporationSpectrum( { 1e-5, 1., 10., 20. }, { 1., 2., 3., 4. }, 2e+6 )
      };
      std::size_t locb = 12;

      MultiEvaporationSpectrum chunk( std::move( probabilities ),
                                      std::move( distributions ),
                                      locb );

      THEN( "a MultiEvaporationSpectrum can be constructed and  members can be "
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

      MultiEvaporationSpectrum chunk( 12, xss.begin(), xss.end() );

      THEN( "a MultiEvaporationSpectrum can be constructed and "
            "members can be tested" ) {

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

  return { // LNW = 32, LAW = 9, IDAT = 21
                     32,                  9,            21,             0,
                      2,               1e-5,  2.000000E+01,  2.500000E-01,
           7.500000E-01,
           // evaporation spectrum
           0,
           4, 1e-5, 2., 5., 20., 5., 6., 7., 8., 1.5e+6,
           // LNW = 0, LAW = 4, IDAT = 41
                      0,                  9,            41,             0,
                      2,               1e-5,  2.000000E+01,  7.500000E-01,
           2.500000E-01,
           // evaporation spectrum
           0,
           4, 1e-5, 1., 10., 20., 1., 2., 3., 4., 2e+6 };
}

void verifyChunk( const MultiEvaporationSpectrum& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 40 == chunk.length() );
  CHECK( "MultiEvaporationSpectrum" == chunk.name() );

  CHECK( EnergyDistributionType::MultiEvaporation == chunk.LAW() );
  CHECK( EnergyDistributionType::MultiEvaporation == chunk.type() );

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
  CHECK( 1e-5 == Approx( probability1.energies()[0] ) );
  CHECK( 20. == Approx( probability1.energies()[1] ) );

  CHECK( 2 == probability1.probabilities().size() );
  CHECK( 0.25 == Approx( probability1.probabilities()[0] ) );
  CHECK( 0.75 == Approx( probability1.probabilities()[1] ) );

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
  CHECK( 1e-5 == Approx( probability2.energies()[0] ) );
  CHECK( 20. == Approx( probability2.energies()[1] ) );

  CHECK( 2 == probability2.probabilities().size() );
  CHECK( 0.75 == Approx( probability2.probabilities()[0] ) );
  CHECK( 0.25 == Approx( probability2.probabilities()[1] ) );

  auto distribution1 = chunk.distribution( 1 );
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

  CHECK( 4 == distribution1.NE() );
  CHECK( 4 == distribution1.numberEnergyPoints() );

  CHECK( 4 == distribution1.energies().size() );
  CHECK( 1e-05 == Approx( distribution1.energies()[0] ) );
  CHECK( 2. == Approx( distribution1.energies()[1] ) );
  CHECK( 5. == Approx( distribution1.energies()[2] ) );
  CHECK( 20. == Approx( distribution1.energies()[3] ) );

  CHECK( 4 == distribution1.temperatures().size() );
  CHECK( 5. == Approx( distribution1.temperatures()[0] ) );
  CHECK( 6. == Approx( distribution1.temperatures()[1] ) );
  CHECK( 7. == Approx( distribution1.temperatures()[2] ) );
  CHECK( 8. == Approx( distribution1.temperatures()[3] ) );

  CHECK( 1e-5 == Approx( distribution1.minimumIncidentEnergy() ) );
  CHECK( 20. == Approx( distribution1.maximumIncidentEnergy() ) );

  CHECK( 1.5e+6 == distribution1.U() );
  CHECK( 1.5e+6 == distribution1.restrictionEnergy() );

  auto distribution2 = chunk.distribution( 2 );
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
  CHECK( 1e-05 == Approx( distribution2.energies()[0] ) );
  CHECK( 1. == Approx( distribution2.energies()[1] ) );
  CHECK( 10. == Approx( distribution2.energies()[2] ) );
  CHECK( 20. == Approx( distribution2.energies()[3] ) );

  CHECK( 4 == distribution2.temperatures().size() );
  CHECK( 1. == Approx( distribution2.temperatures()[0] ) );
  CHECK( 2. == Approx( distribution2.temperatures()[1] ) );
  CHECK( 3. == Approx( distribution2.temperatures()[2] ) );
  CHECK( 4. == Approx( distribution2.temperatures()[3] ) );

  CHECK( 1e-5 == Approx( distribution2.minimumIncidentEnergy() ) );
  CHECK( 20. == Approx( distribution2.maximumIncidentEnergy() ) );

  CHECK( 2e+6 == distribution2.U() );
  CHECK( 2e+6 == distribution2.restrictionEnergy() );
}
