#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/EquiprobableOutgoingEnergyBinData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EquiprobableOutgoingEnergyBinData = block::EquiprobableOutgoingEnergyBinData;
using EquiprobableOutgoingEnergyBins = block::EquiprobableOutgoingEnergyBins;

std::vector< double > chunk();
void verifyChunk( const EquiprobableOutgoingEnergyBinData& );

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

      EquiprobableOutgoingEnergyBinData chunk( xss.begin(), xss.end() );

      THEN( "an EquiprobableOutgoingEnergyBinData can be constructed and members can be tested" ) {

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

void verifyChunk( const EquiprobableOutgoingEnergyBinData& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 13 == chunk.length() );
  CHECK( "DLW::EquiprobableOutgoingEnergyBinData" == chunk.name() );

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
  CHECK( 1e-05 == Approx( chunk.incidentEnergies()[0] ) );
  CHECK( 20. == Approx( chunk.incidentEnergies()[1] ) );

  CHECK( 1e-5 == Approx( chunk.incidentEnergy(1) ) );
  CHECK( 20. == Approx( chunk.incidentEnergy(2) ) );

  CHECK( 1e-5 == Approx( chunk.minimumIncidentEnergy() ) );
  CHECK( 20. == Approx( chunk.maximumIncidentEnergy() ) );

  CHECK( 4 == chunk.NET() );
  CHECK( 3 == chunk.numberBins() );

  auto bins1 = chunk.bins(1);
  CHECK( 1e-5 == Approx( bins1.incidentEnergy() ) );
  CHECK( 3 == bins1.numberBins() );
  CHECK( 4 == bins1.energies().size() );
  CHECK( 1e-4 == Approx( bins1.energies()[0] ) );
  CHECK( 1. == Approx( bins1.energies()[1] ) );
  CHECK( 10. == Approx( bins1.energies()[2] ) );
  CHECK( 20. == Approx( bins1.energies()[3] ) );

  auto bins2 = chunk.bins(2);
  CHECK( 20. == Approx( bins2.incidentEnergy() ) );
  CHECK( 3 == bins2.numberBins() );
  CHECK( 4 == bins2.energies().size() );
  CHECK( 1e-5 == Approx( bins2.energies()[0] ) );
  CHECK( 3. == Approx( bins2.energies()[1] ) );
  CHECK( 12. == Approx( bins2.energies()[2] ) );
  CHECK( 20. == Approx( bins2.energies()[3] ) );
}
