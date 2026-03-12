// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/EditReactionNumberBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EditReactionNumberBlock = multigroup::EditReactionNumberBlock;

std::vector< double > chunk();
void verifyChunk( const EditReactionNumberBlock&, const std::vector< double >& );

SCENARIO( "EditReactionNumberBlock" ) {

  GIVEN( "valid data for a EditReactionNumberBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > reactions = {

                2, 102, 101, 204, 401, 1, 301, 302
              };


      EditReactionNumberBlock chunk( std::move( reactions ) );

      THEN( "a EditReactionNumberBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      EditReactionNumberBlock chunk( xss.begin(), xss.end(), 8 );

      THEN( "a EditReactionNumberBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      EditReactionNumberBlock chunk( xss.begin(), xss.end(), 8 );
      EditReactionNumberBlock copy( chunk );

      THEN( "an EditReactionNumberBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      EditReactionNumberBlock chunk( xss.begin(), xss.end(), 8 );
      EditReactionNumberBlock move( std::move( chunk ) );

      THEN( "an EditReactionNumberBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

             2, 102, 101, 204, 401, 1, 301, 302
  };
}

void verifyChunk( const EditReactionNumberBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // doubleerface

  CHECK( false == chunk.empty() );
  CHECK( 8 == chunk.length() );
  CHECK( "MTED" == chunk.name() );

  CHECK( 8 == chunk.XSS().size() );

  CHECK( 8 == chunk.NEDIT() );
  CHECK( 8 == chunk.numberEditReactions() );
  CHECK( 8 == chunk.editReactionNumbers().size() );
  CHECK( 8 == chunk.MTs().size() );

  CHECK( 2 == chunk.editReactionNumbers().front() );
  CHECK( 302 == chunk.editReactionNumbers().back() );

  unsigned int i = 1;

  CHECK( true == chunk.hasMT(2) );
  CHECK( true == chunk.hasEditReactionNumber(2) );
  CHECK( i == chunk.index(2) );
  CHECK( 2 == chunk.MT(i) );
  CHECK( 2 == chunk.editReactionNumber(i) );

  i++;
  CHECK( true == chunk.hasMT(102) );
  CHECK( true == chunk.hasEditReactionNumber(102) );
  CHECK( i == chunk.index(102) );
  CHECK( 102 == chunk.MT(i) );
  CHECK( 102 == chunk.editReactionNumber(i) );

  i++;
  CHECK( true == chunk.hasMT(101) );
  CHECK( true == chunk.hasEditReactionNumber(101) );
  CHECK( i == chunk.index(101) );
  CHECK( 101 == chunk.MT(i) );
  CHECK( 101 == chunk.editReactionNumber(i) );

  i++;
  CHECK( true == chunk.hasMT(204) );
  CHECK( true == chunk.hasEditReactionNumber(204) );
  CHECK( i == chunk.index(204) );
  CHECK( 204 == chunk.MT(i) );
  CHECK( 204 == chunk.editReactionNumber(i) );

  i++;
  CHECK( true == chunk.hasMT(401) );
  CHECK( true == chunk.hasEditReactionNumber(401) );
  CHECK( i == chunk.index(401) );
  CHECK( 401 == chunk.MT(i) );
  CHECK( 401 == chunk.editReactionNumber(i) );

  i++;
  CHECK( true == chunk.hasMT(1) );
  CHECK( true == chunk.hasEditReactionNumber(1) );
  CHECK( i == chunk.index(1) );
  CHECK( 1 == chunk.MT(i) );
  CHECK( 1 == chunk.editReactionNumber(i) );

  i++;
  CHECK( true == chunk.hasMT(301) );
  CHECK( true == chunk.hasEditReactionNumber(301) );
  CHECK( i == chunk.index(301) );
  CHECK( 301 == chunk.MT(i) );
  CHECK( 301 == chunk.editReactionNumber(i) );

  i++;
  CHECK( true == chunk.hasMT(302) );
  CHECK( true == chunk.hasEditReactionNumber(302) );
  CHECK( i == chunk.index(302) );
  CHECK( 302 == chunk.MT(i) );
  CHECK( 302 == chunk.editReactionNumber(i) );

#ifndef NDEBUG
  i++;
  CHECK_THROWS( chunk.MT(i) );
#endif

  CHECK_THROWS( chunk.index(4) );
}
