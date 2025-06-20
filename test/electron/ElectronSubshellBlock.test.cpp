// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/ElectronSubshellBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ElectronSubshellBlock = electron::ElectronSubshellBlock;

std::vector< double > chunk();
void verifyChunk( const ElectronSubshellBlock&, const std::vector< double >& );
ElectronSubshellBlock makeDummyBlock();

SCENARIO( "ElectronSubshellBlock" ) {

  GIVEN( "valid data for a ElectronSubshellBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > designators = { 1, 2, 3, 4, 5 };
      std::vector< double > electrons = { 2, 2, 2, 4, 2 };
      std::vector< double > energies = { 1.2945e-3, 8.946e-5, 5.655e-5,
                                         5.6240e-5, 6.890e-6 };
      std::vector< double > probabilities = { 1.666666666667E-1, 3.333333333333E-1,
                                              5.000000000000E-1, 8.333333333333E-1,
                                              1.000000000000E+0 };
      std::vector< unsigned int > transitions = { 12, 5, 3, 2, 0 };

      ElectronSubshellBlock chunk( std::move( designators ),
                                   std::move( electrons ),
                                   std::move( energies ),
                                   std::move( probabilities ),
                                   std::move( transitions ) );

      THEN( "a ElectronSubshellBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      ElectronSubshellBlock chunk( xss.begin(), xss.end(), 5 );

      THEN( "a ElectronSubshellBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      ElectronSubshellBlock chunk( xss.begin(), xss.end(), 5 );
      ElectronSubshellBlock copy( chunk );

      THEN( "an ElectronSubshellBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      ElectronSubshellBlock chunk( xss.begin(), xss.end(), 5 );
      ElectronSubshellBlock move( std::move( chunk ) );

      THEN( "an ElectronSubshellBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      ElectronSubshellBlock chunk( xss.begin(), xss.end(), 5 );
      ElectronSubshellBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an ElectronSubshellBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      ElectronSubshellBlock chunk( xss.begin(), xss.end(), 5 );
      ElectronSubshellBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an ElectronSubshellBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
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

void verifyChunk( const ElectronSubshellBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 25 == chunk.length() );
  CHECK( "SUBSH" == chunk.name() );

  CHECK( 5 == chunk.NSSH() );
  CHECK( 5 == chunk.numberElectronSubshells() );

  CHECK( 1 == chunk.ID()[0] );
  CHECK( 2 == chunk.ID()[1] );
  CHECK( 3 == chunk.ID()[2] );
  CHECK( 4 == chunk.ID()[3] );
  CHECK( 5 == chunk.ID()[4] );
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

  CHECK_THAT( 1.2945e-3, WithinRel( chunk.BE()[0] ) );
  CHECK_THAT( 8.9460e-5, WithinRel( chunk.BE()[1] ) );
  CHECK_THAT( 5.6550e-5, WithinRel( chunk.BE()[2] ) );
  CHECK_THAT( 5.6240e-5, WithinRel( chunk.BE()[3] ) );
  CHECK_THAT( 6.8900e-6, WithinRel( chunk.BE()[4] ) );
  CHECK_THAT( 1.2945e-3, WithinRel( chunk.bindingEnergies()[0] ) );
  CHECK_THAT( 8.9460e-5, WithinRel( chunk.bindingEnergies()[1] ) );
  CHECK_THAT( 5.6550e-5, WithinRel( chunk.bindingEnergies()[2] ) );
  CHECK_THAT( 5.6240e-5, WithinRel( chunk.bindingEnergies()[3] ) );
  CHECK_THAT( 6.8900e-6, WithinRel( chunk.bindingEnergies()[4] ) );

  CHECK_THAT( 1.666666666667e-1, WithinRel( chunk.CV()[0] ) );
  CHECK_THAT( 3.333333333333e-1, WithinRel( chunk.CV()[1] ) );
  CHECK_THAT( 5.000000000000e-1, WithinRel( chunk.CV()[2] ) );
  CHECK_THAT( 8.333333333333e-1, WithinRel( chunk.CV()[3] ) );
  CHECK_THAT( 1.000000000000e+0, WithinRel( chunk.CV()[4] ) );
  CHECK_THAT( 1.666666666667e-1, WithinRel( chunk.vacancyProbabilities()[0] ) );
  CHECK_THAT( 3.333333333333e-1, WithinRel( chunk.vacancyProbabilities()[1] ) );
  CHECK_THAT( 5.000000000000e-1, WithinRel( chunk.vacancyProbabilities()[2] ) );
  CHECK_THAT( 8.333333333333e-1, WithinRel( chunk.vacancyProbabilities()[3] ) );
  CHECK_THAT( 1.000000000000e+0, WithinRel( chunk.vacancyProbabilities()[4] ) );

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

  CHECK_THAT( 1.2945e-3, WithinRel( chunk.bindingEnergy( 1 ) ) );
  CHECK_THAT( 8.9460e-5, WithinRel( chunk.bindingEnergy( 2 ) ) );
  CHECK_THAT( 5.6550e-5, WithinRel( chunk.bindingEnergy( 3 ) ) );
  CHECK_THAT( 5.6240e-5, WithinRel( chunk.bindingEnergy( 4 ) ) );
  CHECK_THAT( 6.8900e-6, WithinRel( chunk.bindingEnergy( 5 ) ) );

  CHECK_THAT( 1.666666666667e-1, WithinRel( chunk.vacancyProbability( 1 ) ) );
  CHECK_THAT( 3.333333333333e-1, WithinRel( chunk.vacancyProbability( 2 ) ) );
  CHECK_THAT( 5.000000000000e-1, WithinRel( chunk.vacancyProbability( 3 ) ) );
  CHECK_THAT( 8.333333333333e-1, WithinRel( chunk.vacancyProbability( 4 ) ) );
  CHECK_THAT( 1.000000000000e+0, WithinRel( chunk.vacancyProbability( 5 ) ) );

  CHECK( 12 == chunk.numberTransitions( 1 ) );
  CHECK(  5 == chunk.numberTransitions( 2 ) );
  CHECK(  3 == chunk.numberTransitions( 3 ) );
  CHECK(  2 == chunk.numberTransitions( 4 ) );
  CHECK(  0 == chunk.numberTransitions( 5 ) );
}

ElectronSubshellBlock makeDummyBlock() {

  return { { 1 }, { 2 }, { 1. }, { 3. }, { 5 } };
}
