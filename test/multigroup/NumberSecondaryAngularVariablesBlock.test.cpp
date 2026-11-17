// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/NumberSecondaryAngularVariablesBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using NumberSecondaryAngularVariablesBlock = multigroup::NumberSecondaryAngularVariablesBlock;

std::vector< double > chunk();
void verifyChunk( const NumberSecondaryAngularVariablesBlock&, const std::vector< double >& );
NumberSecondaryAngularVariablesBlock makeDummyBlock();

SCENARIO( "NumberSecondaryAngularVariablesBlock" ) {

  GIVEN( "valid data for a NumberSecondaryAngularVariablesBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > numbers = { 4 };

      NumberSecondaryAngularVariablesBlock chunk( std::move( numbers ) );

      THEN( "a NumberSecondaryAngularVariablesBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      NumberSecondaryAngularVariablesBlock chunk( xss.begin(), xss.end(), 1 );

      THEN( "a NumberSecondaryAngularVariablesBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      NumberSecondaryAngularVariablesBlock chunk( xss.begin(), xss.end(), 1 );
      NumberSecondaryAngularVariablesBlock copy( chunk );

      THEN( "an NumberSecondaryAngularVariablesBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      NumberSecondaryAngularVariablesBlock chunk( xss.begin(), xss.end(), 1 );
      NumberSecondaryAngularVariablesBlock move( std::move( chunk ) );

      THEN( "an NumberSecondaryAngularVariablesBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      NumberSecondaryAngularVariablesBlock chunk( xss.begin(), xss.end(), 1 );
      NumberSecondaryAngularVariablesBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an NumberSecondaryAngularVariablesBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      NumberSecondaryAngularVariablesBlock chunk( xss.begin(), xss.end(), 1 );
      NumberSecondaryAngularVariablesBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an NumberSecondaryAngularVariablesBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 4 };
}

void verifyChunk( const NumberSecondaryAngularVariablesBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 1 == chunk.length() );
  CHECK( "NLEG2" == chunk.name() );

  CHECK( 1 == chunk.NSEC() );
  CHECK( 1 == chunk.numberSecondaryParticles() );

  CHECK( 4  == chunk.NLEG2( 1 ) );
  CHECK( 4  == chunk.numberAngularDistributionVariables( 1 ) );

  CHECK( 1 == chunk.NLEG2s().size() );
  CHECK( 4  == chunk.NLEG2s()[0] );

  CHECK( 1 == chunk.numberAngularDistributionVariablesList().size() );
  CHECK( 4  == chunk.numberAngularDistributionVariablesList()[0] );

}

NumberSecondaryAngularVariablesBlock makeDummyBlock() {

  return { { 1 } };
}
