// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/PrincipalCrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PrincipalCrossSectionBlock = electron::PrincipalCrossSectionBlock;

std::vector< double > chunk();
void verifyChunk( const PrincipalCrossSectionBlock&, const std::vector< double >& );
PrincipalCrossSectionBlock makeDummyBlock();

SCENARIO( "PrincipalCrossSectionBlock" ) {

  GIVEN( "valid data for a PrincipalCrossSectionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 10., 20., 200. };
      std::vector< double > elastic = { 1., 2., 3. };
      std::vector< double > bremsstrahlung = { 4., 5., 6. };
      std::vector< double > excitation = { 7., 8., 9. };
      std::vector< std::vector< double > >
      electroionisation = { { 10., 11., 12. },
                            { 13., 14., 15. } };

      PrincipalCrossSectionBlock
      chunk( std::move( energies ), std::move( elastic ),
             std::move( bremsstrahlung ), std::move( excitation ),
             std::move( electroionisation ) );

      THEN( "a PrincipalCrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      PrincipalCrossSectionBlock chunk( xss.begin(), xss.end(), 2, 3 );

      THEN( "a PrincipalCrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      PrincipalCrossSectionBlock chunk( xss.begin(), xss.end(), 2, 3 );
      PrincipalCrossSectionBlock copy( chunk );

      THEN( "an PrincipalCrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      PrincipalCrossSectionBlock chunk( xss.begin(), xss.end(), 2, 3 );
      PrincipalCrossSectionBlock move( std::move( chunk ) );

      THEN( "an PrincipalCrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      PrincipalCrossSectionBlock chunk( xss.begin(), xss.end(), 2, 3 );
      PrincipalCrossSectionBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an PrincipalCrossSectionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      PrincipalCrossSectionBlock chunk( xss.begin(), xss.end(), 2, 3 );
      PrincipalCrossSectionBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an PrincipalCrossSectionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  // first value of the second xs increased by 1 for testing purposes
  return {  10.,  20., 200.,
            35.,  40.,  45.,
             1.,   2.,   3.,
             4.,   5.,   6.,
             7.,   8.,   9.,
            23.,  25.,  27.,
            10.,  11.,  12.,
            13.,  14.,  15. };
}

void verifyChunk( const PrincipalCrossSectionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 24 == chunk.length() );
  CHECK( "ESZE" == chunk.name() );

  CHECK( 3 == chunk.NE() );
  CHECK( 3 == chunk.numberEnergyPoints() );
  CHECK( 2 == chunk.NSSH() );
  CHECK( 2 == chunk.numberElectronSubshells() );

  CHECK( 3 == chunk.energies().size() );
  CHECK( 3 == chunk.total().size() );
  CHECK( 3 == chunk.elastic().size() );
  CHECK( 3 == chunk.bremsstrahlung().size() );
  CHECK( 3 == chunk.excitation().size() );
  CHECK( 3 == chunk.totalElectroionisation().size() );
  CHECK( 3 == chunk.electroionisation(1).size() );
  CHECK( 3 == chunk.electroionisation(2).size() );

  CHECK_THAT(  10., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT(  20., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 200., WithinRel( chunk.energies()[2] ) );
  CHECK_THAT(  35., WithinRel( chunk.total()[0] ) );
  CHECK_THAT(  40., WithinRel( chunk.total()[1] ) );
  CHECK_THAT(  45., WithinRel( chunk.total()[2] ) );
  CHECK_THAT(   1., WithinRel( chunk.elastic()[0] ) );
  CHECK_THAT(   2., WithinRel( chunk.elastic()[1] ) );
  CHECK_THAT(   3., WithinRel( chunk.elastic()[2] ) );
  CHECK_THAT(   4., WithinRel( chunk.bremsstrahlung()[0] ) );
  CHECK_THAT(   5., WithinRel( chunk.bremsstrahlung()[1] ) );
  CHECK_THAT(   6., WithinRel( chunk.bremsstrahlung()[2] ) );
  CHECK_THAT(   7., WithinRel( chunk.excitation()[0] ) );
  CHECK_THAT(   8., WithinRel( chunk.excitation()[1] ) );
  CHECK_THAT(   9., WithinRel( chunk.excitation()[2] ) );
  CHECK_THAT(  23., WithinRel( chunk.totalElectroionisation()[0] ) );
  CHECK_THAT(  25., WithinRel( chunk.totalElectroionisation()[1] ) );
  CHECK_THAT(  27., WithinRel( chunk.totalElectroionisation()[2] ) );
  CHECK_THAT(  10., WithinRel( chunk.electroionisation(1)[0] ) );
  CHECK_THAT(  11., WithinRel( chunk.electroionisation(1)[1] ) );
  CHECK_THAT(  12., WithinRel( chunk.electroionisation(1)[2] ) );
  CHECK_THAT(  13., WithinRel( chunk.electroionisation(2)[0] ) );
  CHECK_THAT(  14., WithinRel( chunk.electroionisation(2)[1] ) );
  CHECK_THAT(  15., WithinRel( chunk.electroionisation(2)[2] ) );
}

PrincipalCrossSectionBlock makeDummyBlock() {

  return { { 1., 2. }, { 3., 4. }, { 5., 6. }, { 7., 8. },
           { { 1., 2. }, { 3., 4. } } };
}
