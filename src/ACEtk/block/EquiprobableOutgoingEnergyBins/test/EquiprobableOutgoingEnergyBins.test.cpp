#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/EquiprobableOutgoingEnergyBins.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EquiprobableOutgoingEnergyBins = block::EquiprobableOutgoingEnergyBins;

std::vector< double > chunk();
void verifyChunk( const EquiprobableOutgoingEnergyBins& );

SCENARIO( "EquiprobableOutgoingEnergyBins" ) {

  GIVEN( "valid data for an EquiprobableOutgoingEnergyBins instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double incident = 2.1;
      std::vector< double > energies = { 1e-5, 2e-2, 1., 20. };

      EquiprobableOutgoingEnergyBins chunk( incident, std::move( energies ) );

      THEN( "an EquiprobableOutgoingEnergyBins can be constructed and members can be "
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

      double incident = 2.1;
      EquiprobableOutgoingEnergyBins chunk( incident, xss.begin(), xss.end() );

      THEN( "an EquiprobableOutgoingEnergyBins can be constructed and members can be tested" ) {

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

     1.00000000000E-05,  2.00000000000E-02,  1.00000000000E+00,  2.00000000000E+01
  };
}

void verifyChunk( const EquiprobableOutgoingEnergyBins& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 4 == chunk.length() );
  CHECK( "AND::EquiprobableOutgoingEnergyBins" == chunk.name() );

  CHECK( 2.1 == Approx( chunk.incidentEnergy() ) );
  CHECK( 3 == chunk.numberBins() );

  CHECK( 4 == chunk.outgoingEnergies().size() );
  CHECK( 1e-5 == Approx( chunk.outgoingEnergies()[0] ) );
  CHECK( .02 == Approx( chunk.outgoingEnergies()[1] ) );
  CHECK( 1. == Approx( chunk.outgoingEnergies()[2] ) );
  CHECK( 20. == Approx( chunk.outgoingEnergies()[3] ) );
}
