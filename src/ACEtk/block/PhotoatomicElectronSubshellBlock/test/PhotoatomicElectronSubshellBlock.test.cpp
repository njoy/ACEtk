#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/PhotoatomicElectronSubshellBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PhotoatomicElectronSubshellBlock = block::PhotoatomicElectronSubshellBlock;

std::vector< double > chunk();
void verifyChunk( const PhotoatomicElectronSubshellBlock& );

SCENARIO( "PhotoatomicElectronSubshellBlock" ) {

  GIVEN( "valid data for a PhotoatomicElectronSubshellBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > designators = { 1, 2, 3, 4, 5 };
      std::vector< unsigned int > electrons = { 2, 2, 2, 4, 2 };
      std::vector< double > energies = { 1.2945e-3, 8.946e-5, 5.655e-5,
                                         5.6240e-5, 6.890e-6 };
      std::vector< double > probabilities = { 1.666666666667E-1, 3.333333333333E-1,
                                              5.000000000000E-1, 8.333333333333E-1,
                                              1.000000000000E+0 };
      std::vector< unsigned int > transitions = { 12, 5, 3, 2, 0 };

      PhotoatomicElectronSubshellBlock chunk( std::move( designators ),
                                              std::move( electrons ),
                                              std::move( energies ),
                                              std::move( probabilities ),
                                              std::move( transitions ) );

      THEN( "a PhotoatomicElectronShellBlock can be constructed and members can "
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

      PhotoatomicElectronSubshellBlock chunk( xss.begin(), xss.end(), 5 );

      THEN( "a PhotoatomicElectronShellBlock can be constructed and members can "
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

  return {                                                             1.000000000000E+00,
           2.000000000000E+00, 3.000000000000E+00, 4.000000000000E+00, 5.000000000000E+00,
           2.000000000000E+00, 2.000000000000E+00, 2.000000000000E+00, 4.000000000000E+00,
           2.000000000000E+00, 1.294500000000E-03, 8.946000000000E-05, 5.655000000000E-05,
           5.624000000000E-05, 6.890000000000E-06, 1.666666666667E-01, 3.333333333333E-01,
           5.000000000000E-01, 8.333333333333E-01, 1.000000000000E+00, 1.200000000000E+01,
           5.000000000000E+00, 3.000000000000E+00, 2.000000000000E+00, 0.000000000000E+00 };
}

void verifyChunk( const PhotoatomicElectronSubshellBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 25 == chunk.length() );
  CHECK( "SUBSH" == chunk.name() );

  CHECK( 5 == chunk.NSSH() );
  CHECK( 5 == chunk.numberElectronSubshells() );

  CHECK( 1 == chunk.ENDF()[0] );
  CHECK( 2 == chunk.ENDF()[1] );
  CHECK( 3 == chunk.ENDF()[2] );
  CHECK( 4 == chunk.ENDF()[3] );
  CHECK( 5 == chunk.ENDF()[4] );
  CHECK( 1 == chunk.designators()[0] );
  CHECK( 2 == chunk.designators()[1] );
  CHECK( 3 == chunk.designators()[2] );
  CHECK( 4 == chunk.designators()[3] );
  CHECK( 5 == chunk.designators()[4] );

  CHECK( 2 == chunk.EP()[0] );
  CHECK( 2 == chunk.EP()[1] );
  CHECK( 2 == chunk.EP()[2] );
  CHECK( 4 == chunk.EP()[3] );
  CHECK( 2 == chunk.EP()[4] );
  CHECK( 2 == chunk.populations()[0] );
  CHECK( 2 == chunk.populations()[1] );
  CHECK( 2 == chunk.populations()[2] );
  CHECK( 4 == chunk.populations()[3] );
  CHECK( 2 == chunk.populations()[4] );

  CHECK( 1.2945e-3 == Approx( chunk.BE()[0] ) );
  CHECK( 8.9460e-5 == Approx( chunk.BE()[1] ) );
  CHECK( 5.6550e-5 == Approx( chunk.BE()[2] ) );
  CHECK( 5.6240e-5 == Approx( chunk.BE()[3] ) );
  CHECK( 6.8900e-6 == Approx( chunk.BE()[4] ) );
  CHECK( 1.2945e-3 == Approx( chunk.bindingEnergies()[0] ) );
  CHECK( 8.9460e-5 == Approx( chunk.bindingEnergies()[1] ) );
  CHECK( 5.6550e-5 == Approx( chunk.bindingEnergies()[2] ) );
  CHECK( 5.6240e-5 == Approx( chunk.bindingEnergies()[3] ) );
  CHECK( 6.8900e-6 == Approx( chunk.bindingEnergies()[4] ) );

  CHECK( 1.666666666667e-1 == Approx( chunk.CV()[0] ) );
  CHECK( 3.333333333333e-1 == Approx( chunk.CV()[1] ) );
  CHECK( 5.000000000000e-1 == Approx( chunk.CV()[2] ) );
  CHECK( 8.333333333333e-1 == Approx( chunk.CV()[3] ) );
  CHECK( 1.000000000000e+0 == Approx( chunk.CV()[4] ) );
  CHECK( 1.666666666667e-1 == Approx( chunk.vacancyProbabilities()[0] ) );
  CHECK( 3.333333333333e-1 == Approx( chunk.vacancyProbabilities()[1] ) );
  CHECK( 5.000000000000e-1 == Approx( chunk.vacancyProbabilities()[2] ) );
  CHECK( 8.333333333333e-1 == Approx( chunk.vacancyProbabilities()[3] ) );
  CHECK( 1.000000000000e+0 == Approx( chunk.vacancyProbabilities()[4] ) );

  CHECK( 12 == chunk.NT()[0] );
  CHECK(  5 == chunk.NT()[1] );
  CHECK(  3 == chunk.NT()[2] );
  CHECK(  2 == chunk.NT()[3] );
  CHECK(  0 == chunk.NT()[4] );
  CHECK( 12 == chunk.numberTransitions()[0] );
  CHECK(  5 == chunk.numberTransitions()[1] );
  CHECK(  3 == chunk.numberTransitions()[2] );
  CHECK(  2 == chunk.numberTransitions()[3] );
  CHECK(  0 == chunk.numberTransitions()[4] );

  CHECK( 1 == chunk.designator( 1 ) );
  CHECK( 2 == chunk.designator( 2 ) );
  CHECK( 3 == chunk.designator( 3 ) );
  CHECK( 4 == chunk.designator( 4 ) );
  CHECK( 5 == chunk.designator( 5 ) );

  CHECK( 2 == chunk.population( 1 ) );
  CHECK( 2 == chunk.population( 2 ) );
  CHECK( 2 == chunk.population( 3 ) );
  CHECK( 4 == chunk.population( 4 ) );
  CHECK( 2 == chunk.population( 5 ) );

  CHECK( 1.2945e-3 == Approx( chunk.bindingEnergy( 1 ) ) );
  CHECK( 8.9460e-5 == Approx( chunk.bindingEnergy( 2 ) ) );
  CHECK( 5.6550e-5 == Approx( chunk.bindingEnergy( 3 ) ) );
  CHECK( 5.6240e-5 == Approx( chunk.bindingEnergy( 4 ) ) );
  CHECK( 6.8900e-6 == Approx( chunk.bindingEnergy( 5 ) ) );

  CHECK( 1.666666666667e-1 == Approx( chunk.vacancyProbability( 1 ) ) );
  CHECK( 3.333333333333e-1 == Approx( chunk.vacancyProbability( 2 ) ) );
  CHECK( 5.000000000000e-1 == Approx( chunk.vacancyProbability( 3 ) ) );
  CHECK( 8.333333333333e-1 == Approx( chunk.vacancyProbability( 4 ) ) );
  CHECK( 1.000000000000e+0 == Approx( chunk.vacancyProbability( 5 ) ) );

  CHECK( 12 == chunk.numberTransitions( 1 ) );
  CHECK(  5 == chunk.numberTransitions( 2 ) );
  CHECK(  3 == chunk.numberTransitions( 3 ) );
  CHECK(  2 == chunk.numberTransitions( 4 ) );
  CHECK(  0 == chunk.numberTransitions( 5 ) );
}
