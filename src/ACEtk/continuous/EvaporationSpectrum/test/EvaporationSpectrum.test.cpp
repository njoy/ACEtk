#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/continuous/EvaporationSpectrum.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EvaporationSpectrum = continuous::EvaporationSpectrum;

std::vector< double > chunk();
void verifyChunk( const EvaporationSpectrum& );

SCENARIO( "EvaporationSpectrum" ) {

  GIVEN( "valid data for a EvaporationSpectrum instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 1e-5, 1., 10., 20. };
      std::vector< double > temperatures = { 1., 2., 3., 4. };
      double energy = 1.5e+6;

      EvaporationSpectrum chunk( std::move( energies ),
                                            std::move( temperatures ),
                                            energy );

      THEN( "a EvaporationSpectrum can be constructed and "
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

    WHEN( "the data is defined by iterators" ) {

      EvaporationSpectrum chunk( xss.begin(), xss.end() );

      THEN( "an EvaporationSpectrum can be constructed and members can be "
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

  return { 0,
           4, 1e-5, 1., 10., 20., 1., 2., 3., 4.,
           1.5e+6 };
}

void verifyChunk( const EvaporationSpectrum& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 11 == chunk.length() );
  CHECK( "EvaporationSpectrum" == chunk.name() );

  CHECK( EnergyDistributionType::Evaporation == chunk.LAW() );
  CHECK( EnergyDistributionType::Evaporation == chunk.type() );

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

  CHECK( 4 == chunk.NE() );
  CHECK( 4 == chunk.numberEnergyPoints() );

  CHECK( 4 == chunk.energies().size() );
  CHECK( 1e-05 == Approx( chunk.energies()[0] ) );
  CHECK( 1. == Approx( chunk.energies()[1] ) );
  CHECK( 10. == Approx( chunk.energies()[2] ) );
  CHECK( 20. == Approx( chunk.energies()[3] ) );

  CHECK( 4 == chunk.temperatures().size() );
  CHECK( 1. == Approx( chunk.temperatures()[0] ) );
  CHECK( 2. == Approx( chunk.temperatures()[1] ) );
  CHECK( 3. == Approx( chunk.temperatures()[2] ) );
  CHECK( 4. == Approx( chunk.temperatures()[3] ) );

  CHECK( 1e-5 == Approx( chunk.minimumIncidentEnergy() ) );
  CHECK( 20. == Approx( chunk.maximumIncidentEnergy() ) );

  CHECK( 1.5e+6 == chunk.U() );
  CHECK( 1.5e+6 == chunk.restrictionEnergy() );
}
