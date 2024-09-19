// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/EnergyDependentWattSpectrum.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EnergyDependentWattSpectrum = continuous::EnergyDependentWattSpectrum;
using ParameterData = continuous::ParameterData;

std::vector< double > chunk();
void verifyChunk( const EnergyDependentWattSpectrum&, const std::vector< double >& );
EnergyDependentWattSpectrum makeDummyBlock();

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

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      EnergyDependentWattSpectrum chunk( xss.begin(), xss.end() );

      THEN( "an EnergyDependentWattSpectrum can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 0, 4, 1e-5, 1., 10., 20., 1., 2., 3., 4.,
           0, 3, 1e-5, 2., 20., 5., 6., 7.,
           1.5e+6 };
}

void verifyChunk( const EnergyDependentWattSpectrum& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

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
  CHECK_THAT( 1e-05, WithinRel( a.energies()[0] ) );
  CHECK_THAT( 1., WithinRel( a.energies()[1] ) );
  CHECK_THAT( 10., WithinRel( a.energies()[2] ) );
  CHECK_THAT( 20., WithinRel( a.energies()[3] ) );

  CHECK( 4 == a.values().size() );
  CHECK_THAT( 1., WithinRel( a.values()[0] ) );
  CHECK_THAT( 2., WithinRel( a.values()[1] ) );
  CHECK_THAT( 3., WithinRel( a.values()[2] ) );
  CHECK_THAT( 4., WithinRel( a.values()[3] ) );

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
  CHECK_THAT( 1e-05, WithinRel( b.energies()[0] ) );
  CHECK_THAT( 2., WithinRel( b.energies()[1] ) );
  CHECK_THAT( 20., WithinRel( b.energies()[2] ) );

  CHECK( 3 == b.values().size() );
  CHECK_THAT( 5., WithinRel( b.values()[0] ) );
  CHECK_THAT( 6., WithinRel( b.values()[1] ) );
  CHECK_THAT( 7., WithinRel( b.values()[2] ) );

  CHECK_THAT( 1e-5, WithinRel( chunk.minimumIncidentEnergy() ) );
  CHECK_THAT( 20., WithinRel( chunk.maximumIncidentEnergy() ) );

  CHECK( 1.5e+6 == chunk.U() );
  CHECK( 1.5e+6 == chunk.restrictionEnergy() );
}
