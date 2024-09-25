// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/dosimetry/CrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using CrossSectionBlock = dosimetry::CrossSectionBlock;
using CrossSectionData = dosimetry::CrossSectionData;

std::vector< double > chunk();
void verifyChunk( const CrossSectionBlock&, const std::vector< double >& );
CrossSectionBlock makeDummyBlock();

SCENARIO( "CrossSectionBlock" ) {

  GIVEN( "valid data for a CrossSectionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< CrossSectionData > xs = {

        CrossSectionData(
          { 1.896100000000E+00,  2.000000000000E+00,
            2.050000000000E+00,  2.000000000000E+01 },
          { 0.000000000000E+00,  9.090000000000E-15,
            3.638500000000E-02,  3.220000000000E-02 } ),
        CrossSectionData(
          { 3.248700000000E+00,  3.600000000000E+00,  2.000000000000E+01 },
          { 0.000000000000E+00,  5.653700000000E-02,  4.980000000000E-02 } ) };

      CrossSectionBlock chunk( std::move( xs ) );

      THEN( "a CrossSectionBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      CrossSectionBlock chunk( xss.begin(), xss.begin() + 2, xss.end(), 2 );

      THEN( "a CrossSectionBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      CrossSectionBlock chunk( xss.begin(), xss.begin() + 2, xss.end(), 2 );
      CrossSectionBlock copy( chunk );

      THEN( "an CrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      CrossSectionBlock chunk( xss.begin(), xss.begin() + 2, xss.end(), 2 );
      CrossSectionBlock move( std::move( chunk ) );

      THEN( "an CrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      CrossSectionBlock chunk( xss.begin(), xss.begin() + 2, xss.end(), 2 );
      CrossSectionBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an CrossSectionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      CrossSectionBlock chunk( xss.begin(), xss.begin() + 2, xss.end(), 2 );
      CrossSectionBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an CrossSectionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

                    1,                  11,
                    0,                   4,  1.896100000000E+00,  2.000000000000E+00,
   2.050000000000E+00,  2.000000000000E+01,  0.000000000000E+00,  9.090000000000E-15,
   3.638500000000E-02,  3.220000000000E-02,                   0,                   3,
   3.248700000000E+00,  3.600000000000E+00,  2.000000000000E+01,  0.000000000000E+00,
   5.653700000000E-02,  4.980000000000E-02 };
}

void verifyChunk( const CrossSectionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 20 == chunk.length() );
  CHECK( "SIGD" == chunk.name() );

  CHECK( 2 == chunk.NTR() );
  CHECK( 2 == chunk.numberReactions() );

  CHECK( 1 == chunk.LSIG(1) );
  CHECK( 11 == chunk.LSIG(2) );
  CHECK( 1 == chunk.crossSectionLocator(1) );
  CHECK( 11 == chunk.crossSectionLocator(2) );

  auto xs = chunk.crossSectionData(1);
  CHECK( 0 == xs.NB() );
  CHECK( 4 == xs.numberEnergyPoints() );
  CHECK( 4 == xs.energies().size() );
  CHECK( 4 == xs.crossSections().size() );
  CHECK_THAT( 1.8961, WithinRel( xs.energies().front() ) );
  CHECK_THAT( 20., WithinRel( xs.energies().back() ) );
  CHECK_THAT( 0., WithinRel( xs.crossSections().front() ) );
  CHECK_THAT( 0.0322, WithinRel( xs.crossSections().back() ) );

  xs = chunk.crossSectionData(2);
  CHECK( 0 == xs.NB() );
  CHECK( 3 == xs.numberEnergyPoints() );
  CHECK( 3 == xs.energies().size() );
  CHECK( 3 == xs.crossSections().size() );
  CHECK_THAT( 3.2487, WithinRel( xs.energies().front() ) );
  CHECK_THAT( 20., WithinRel( xs.energies().back() ) );
  CHECK_THAT( 0., WithinRel( xs.crossSections().front() ) );
  CHECK_THAT( 0.0498, WithinRel( xs.crossSections().back() ) );
}

CrossSectionBlock makeDummyBlock() {

  return { { { { 1., 2. }, { 3., 4. } } } };
}
