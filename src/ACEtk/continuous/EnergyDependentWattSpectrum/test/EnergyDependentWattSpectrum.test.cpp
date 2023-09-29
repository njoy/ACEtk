#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/continuous/ParameterData.hpp"
#include "ACEtk/continuous/EnergyDependentWattSpectrum.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EnergyDependentWattSpectrum = block::EnergyDependentWattSpectrum;
using ParameterData = block::ParameterData;

std::vector< double > chunk();
void verifyChunk( const EnergyDependentWattSpectrum& );

SCENARIO( "EnergyDependentWattSpectrum" ) {

  GIVEN( "valid data for an EnergyDependentWattSpectrum instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      ParameterData a( { 1e-5, 1., 10., 20. }, { 1., 2., 3., 4. } );
      ParameterData b( { 1e-5, 2., 20. }, { 5., 6., 7. } );
      double energy = 1.5e+6;

      EnergyDependentWattSpectrum chunk( std::move( a ), std::move( b ),
                                         energy );

      THEN( "an EnergyDependentWattSpectrum can be constructed and "
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

      EnergyDependentWattSpectrum chunk( xss.begin(), xss.end() );

      THEN( "an EnergyDependentWattSpectrum can be constructed and members "
            "can be tested" ) {

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

  return { 0, 4, 1e-5, 1., 10., 20., 1., 2., 3., 4.,
           0, 3, 1e-5, 2., 20., 5., 6., 7.,
           1.5e+6 };
}

void verifyChunk( const EnergyDependentWattSpectrum& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 19 == chunk.length() );
  CHECK( "EnergyDependentWattSpectrum" == chunk.name() );

  CHECK( EnergyDistributionType::Watt == chunk.LAW() );
  CHECK( EnergyDistributionType::Watt == chunk.type() );

  auto a = chunk.a();
  CHECK( 0 == a.interpolationData().NB() );
  CHECK( 0 == a.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == a.interpolationData().INT().size() );
  CHECK( 0 == a.interpolationData().interpolants().size() );
  CHECK( 0 == a.interpolationData().NBT().size() );
  CHECK( 0 == a.interpolationData().boundaries().size() );

  CHECK( 0 == a.NB() );
  CHECK( 0 == a.numberInterpolationRegions() );
  CHECK( 0 == a.INT().size() );
  CHECK( 0 == a.interpolants().size() );
  CHECK( 0 == a.NBT().size() );
  CHECK( 0 == a.boundaries().size() );

  CHECK( 4 == a.NE() );
  CHECK( 4 == a.numberEnergyPoints() );

  CHECK( 4 == a.energies().size() );
  CHECK( 1e-05 == Approx( a.energies()[0] ) );
  CHECK( 1. == Approx( a.energies()[1] ) );
  CHECK( 10. == Approx( a.energies()[2] ) );
  CHECK( 20. == Approx( a.energies()[3] ) );

  CHECK( 4 == a.values().size() );
  CHECK( 1. == Approx( a.values()[0] ) );
  CHECK( 2. == Approx( a.values()[1] ) );
  CHECK( 3. == Approx( a.values()[2] ) );
  CHECK( 4. == Approx( a.values()[3] ) );

  auto b = chunk.b();
  CHECK( 0 == b.interpolationData().NB() );
  CHECK( 0 == b.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == b.interpolationData().INT().size() );
  CHECK( 0 == b.interpolationData().interpolants().size() );
  CHECK( 0 == b.interpolationData().NBT().size() );
  CHECK( 0 == b.interpolationData().boundaries().size() );

  CHECK( 0 == b.NB() );
  CHECK( 0 == b.numberInterpolationRegions() );
  CHECK( 0 == b.INT().size() );
  CHECK( 0 == b.interpolants().size() );
  CHECK( 0 == b.NBT().size() );
  CHECK( 0 == b.boundaries().size() );

  CHECK( 3 == b.NE() );
  CHECK( 3 == b.numberEnergyPoints() );

  CHECK( 3 == b.energies().size() );
  CHECK( 1e-05 == Approx( b.energies()[0] ) );
  CHECK( 2. == Approx( b.energies()[1] ) );
  CHECK( 20. == Approx( b.energies()[2] ) );

  CHECK( 3 == b.values().size() );
  CHECK( 5. == Approx( b.values()[0] ) );
  CHECK( 6. == Approx( b.values()[1] ) );
  CHECK( 7. == Approx( b.values()[2] ) );

  CHECK( 1e-5 == Approx( chunk.minimumIncidentEnergy() ) );
  CHECK( 20. == Approx( chunk.maximumIncidentEnergy() ) );

  CHECK( 1.5e+6 == chunk.U() );
  CHECK( 1.5e+6 == chunk.restrictionEnergy() );
}
