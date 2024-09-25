// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/EquiprobableOutgoingEnergyBinData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EquiprobableOutgoingEnergyBinData = continuous::EquiprobableOutgoingEnergyBinData;
using EquiprobableOutgoingEnergyBins = continuous::EquiprobableOutgoingEnergyBins;

std::vector< double > chunk();
void verifyChunk( const EquiprobableOutgoingEnergyBinData&, const std::vector< double >& );
EquiprobableOutgoingEnergyBinData makeDummyBlock();

SCENARIO( "EquiprobableOutgoingEnergyBinData" ) {

  GIVEN( "valid data for an EquiprobableOutgoingEnergyBinData instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< EquiprobableOutgoingEnergyBins > distributions = {

        EquiprobableOutgoingEnergyBins( 1e-5, { 1e-4, 1., 10., 20. } ),
        EquiprobableOutgoingEnergyBins( 20., { 1e-5, 3., 12., 20. } )
      };

      EquiprobableOutgoingEnergyBinData chunk( std::move( distributions ) );

      THEN( "an EquiprobableOutgoingEnergyBinData can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      EquiprobableOutgoingEnergyBinData chunk( xss.begin(), xss.end() );

      THEN( "an EquiprobableOutgoingEnergyBinData can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      EquiprobableOutgoingEnergyBinData chunk( xss.begin(), xss.end() );
      EquiprobableOutgoingEnergyBinData copy( chunk );

      THEN( "an EquiprobableOutgoingEnergyBinData can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      EquiprobableOutgoingEnergyBinData chunk( xss.begin(), xss.end() );
      EquiprobableOutgoingEnergyBinData move( std::move( chunk ) );

      THEN( "an EquiprobableOutgoingEnergyBinData can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      EquiprobableOutgoingEnergyBinData chunk( xss.begin(), xss.end() );
      EquiprobableOutgoingEnergyBinData copy = makeDummyBlock();
      copy = chunk;

      THEN( "an EquiprobableOutgoingEnergyBinData can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      EquiprobableOutgoingEnergyBinData chunk( xss.begin(), xss.end() );
      EquiprobableOutgoingEnergyBinData move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an EquiprobableOutgoingEnergyBinData can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {
           // NR
                           0,
           // NE and incident energy values
                           2,
                      1.0e-5,  2.00000000000E+01,
           // NET and outgoing energy values
                           4,
           1.00000000000E-04,  1.00000000000E+00,  1.00000000000E+01,  2.00000000000E+01,
           1.00000000000E-05,  3.00000000000E+00,  1.20000000000E+01,  2.00000000000E+01 };
}

void verifyChunk( const EquiprobableOutgoingEnergyBinData& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 13 == chunk.length() );
  CHECK( "EquiprobableOutgoingEnergyBinData" == chunk.name() );

  CHECK( EnergyDistributionType::Equiprobable == chunk.LAW() );
  CHECK( EnergyDistributionType::Equiprobable == chunk.type() );

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
  CHECK_THAT( 1e-05, WithinRel( chunk.incidentEnergies()[0] ) );
  CHECK_THAT( 20., WithinRel( chunk.incidentEnergies()[1] ) );

  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergy(1) ) );
  CHECK_THAT( 20., WithinRel( chunk.incidentEnergy(2) ) );

  CHECK_THAT( 1e-5, WithinRel( chunk.minimumIncidentEnergy() ) );
  CHECK_THAT( 20., WithinRel( chunk.maximumIncidentEnergy() ) );

  CHECK( 4 == chunk.NET() );
  CHECK( 3 == chunk.numberBins() );

  decltype(auto) distributions = chunk.distributions();
  CHECK( 2 == distributions.size() );

  CHECK_THAT( 1e-5, WithinRel( distributions[0].incidentEnergy() ) );
  CHECK( 3 == distributions[0].numberBins() );
  CHECK( 4 == distributions[0].energies().size() );
  CHECK_THAT( 1e-4, WithinRel( distributions[0].energies()[0] ) );
  CHECK_THAT( 1., WithinRel( distributions[0].energies()[1] ) );
  CHECK_THAT( 10., WithinRel( distributions[0].energies()[2] ) );
  CHECK_THAT( 20., WithinRel( distributions[0].energies()[3] ) );

  CHECK_THAT( 20., WithinRel( distributions[1].incidentEnergy() ) );
  CHECK( 3 == distributions[1].numberBins() );
  CHECK( 4 == distributions[1].energies().size() );
  CHECK_THAT( 1e-5, WithinRel( distributions[1].energies()[0] ) );
  CHECK_THAT( 3., WithinRel( distributions[1].energies()[1] ) );
  CHECK_THAT( 12., WithinRel( distributions[1].energies()[2] ) );
  CHECK_THAT( 20., WithinRel( distributions[1].energies()[3] ) );

  auto bins1 = chunk.distribution(1);
  CHECK_THAT( 1e-5, WithinRel( bins1.incidentEnergy() ) );
  CHECK( 3 == bins1.numberBins() );
  CHECK( 4 == bins1.energies().size() );
  CHECK_THAT( 1e-4, WithinRel( bins1.energies()[0] ) );
  CHECK_THAT( 1., WithinRel( bins1.energies()[1] ) );
  CHECK_THAT( 10., WithinRel( bins1.energies()[2] ) );
  CHECK_THAT( 20., WithinRel( bins1.energies()[3] ) );

  auto bins2 = chunk.distribution(2);
  CHECK_THAT( 20., WithinRel( bins2.incidentEnergy() ) );
  CHECK( 3 == bins2.numberBins() );
  CHECK( 4 == bins2.energies().size() );
  CHECK_THAT( 1e-5, WithinRel( bins2.energies()[0] ) );
  CHECK_THAT( 3., WithinRel( bins2.energies()[1] ) );
  CHECK_THAT( 12., WithinRel( bins2.energies()[2] ) );
  CHECK_THAT( 20., WithinRel( bins2.energies()[3] ) );
}

EquiprobableOutgoingEnergyBinData makeDummyBlock() {

  std::vector< EquiprobableOutgoingEnergyBins > distributions = {

    EquiprobableOutgoingEnergyBins( 1e-3, { 1e-3, 20. } ),
    EquiprobableOutgoingEnergyBins( 10., { 1e-4, 10. } )
  };

  return { std::move( distributions ) };
}