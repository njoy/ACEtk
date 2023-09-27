#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/electron/ElectronShellBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ElectronShellBlock = electron::ElectronShellBlock;

std::vector< double > chunk();
void verifyChunk( const ElectronShellBlock& );

SCENARIO( "ElectronShellBlock" ) {

  GIVEN( "valid data for a ElectronShellBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > electrons = { 2, 1 };
      std::vector< double > energies = { 5.480000000000e-05, 1.000000000000e-06 };
      std::vector< double > probabilities = { 6.666666666667e-01, 3.333333333333e-01 };

      ElectronShellBlock chunk( std::move( electrons ),
                                         std::move( energies ),
                                         std::move( probabilities ) );

      THEN( "a ElectronShellBlock can be constructed and members can "
            "be tested" ) {

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

      ElectronShellBlock chunk( xss.begin(), xss.end(), 2 );

      THEN( "a ElectronShellBlock can be constructed and members can "
            "be tested" ) {

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

  return {                                                                                 2,
                            1,  5.480000000000e-05,  1.000000000000e-06,  6.666666666667e-01,
           3.333333333333e-01 };
}

void verifyChunk( const ElectronShellBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 6 == chunk.length() );
  CHECK( "EPS" == chunk.name() );

  CHECK( 2 == chunk.NSH() );
  CHECK( 2 == chunk.numberElectronShells() );

  CHECK( 2 == Approx( chunk.numberElectrons()[0] ) );
  CHECK( 1 == Approx( chunk.numberElectrons()[1] ) );
  CHECK( 5.480000000000e-05 == Approx( chunk.bindingEnergies()[0] ) );
  CHECK( 1.000000000000e-06 == Approx( chunk.bindingEnergies()[1] ) );
  CHECK( 6.666666666667e-01 == Approx( chunk.interactionProbabilities()[0] ) );
  CHECK( 3.333333333333e-01 == Approx( chunk.interactionProbabilities()[1] ) );

  CHECK( 2 == chunk.numberElectronsPerShell( 1 ) );
  CHECK( 1 == chunk.numberElectronsPerShell( 2 ) );
  CHECK( 5.480000000000e-05 == Approx( chunk.bindingEnergy( 1 ) ) );
  CHECK( 1.000000000000e-06 == Approx( chunk.bindingEnergy( 2 ) ) );
  CHECK( 6.666666666667e-01 == Approx( chunk.interactionProbability( 1 ) ) );
  CHECK( 3.333333333333e-01 == Approx( chunk.interactionProbability( 2 ) ) );
}
