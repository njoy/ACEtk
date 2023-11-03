// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
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

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
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

  CHECK( 2 == chunk.numberElectrons()[0] );
  CHECK( 1 == chunk.numberElectrons()[1] );
  CHECK_THAT( 5.480000000000e-05, WithinRel( chunk.bindingEnergies()[0] ) );
  CHECK_THAT( 1.000000000000e-06, WithinRel( chunk.bindingEnergies()[1] ) );
  CHECK_THAT( 6.666666666667e-01, WithinRel( chunk.interactionProbabilities()[0] ) );
  CHECK_THAT( 3.333333333333e-01, WithinRel( chunk.interactionProbabilities()[1] ) );

  CHECK( 2 == chunk.numberElectronsPerShell( 1 ) );
  CHECK( 1 == chunk.numberElectronsPerShell( 2 ) );
  CHECK_THAT( 5.480000000000e-05, WithinRel( chunk.bindingEnergy( 1 ) ) );
  CHECK_THAT( 1.000000000000e-06, WithinRel( chunk.bindingEnergy( 2 ) ) );
  CHECK_THAT( 6.666666666667e-01, WithinRel( chunk.interactionProbability( 1 ) ) );
  CHECK_THAT( 3.333333333333e-01, WithinRel( chunk.interactionProbability( 2 ) ) );
}
