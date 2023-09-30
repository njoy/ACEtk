// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/SubshellTransitionData.hpp"

// other includes
#include "ACEtk/fromFile.hpp"

// convenience typedefs
using namespace njoy::ACEtk;
using SubshellTransitionData = electron::SubshellTransitionData;

std::vector< double > chunk();
void verifyChunk( const SubshellTransitionData& );

SCENARIO( "SubshellTransitionData" ) {

  GIVEN( "valid data for a SubshellTransitionData instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > primary = { 1, 2, 3 };
      std::vector< unsigned int > secondary = { 0, 3, 1 };
      std::vector< double > energies = { 3.5, 2.5, 5.5 };
      std::vector< double > probabilities = { 0.25, 0.75, 1. };

      SubshellTransitionData
      chunk( std::move( primary ), std::move( secondary ),
             std::move( energies ), std::move( probabilities ) );

      THEN( "a SubshellTransitionData can be constructed and "
            "members can be tested" ) {

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

      SubshellTransitionData chunk( xss.begin(), xss.end() );

      THEN( "a SubshellTransitionData can be constructed and "
            "members can be tested" ) {

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

  // first value of the second xs increased by 1 for testing purposes
  return {   1,   0,   3.5, 0.25,
             2,   3,   2.5, 0.75,
             3,   1,   5.5, 1.00 };
}

void verifyChunk( const SubshellTransitionData& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 12 == chunk.length() );
  CHECK( "TRAN" == chunk.name() );

  CHECK( 3 == chunk.NT() );
  CHECK( 3 == chunk.numberTransitions() );

  CHECK( 4 == chunk.transition(1).size() );
  CHECK( 4 == chunk.transition(2).size() );
  CHECK( 4 == chunk.transition(3).size() );

  CHECK_THAT(    1, WithinRel( chunk.transition(1)[0] ) );
  CHECK_THAT(    0, WithinRel( chunk.transition(1)[1] ) );
  CHECK_THAT(  3.5, WithinRel( chunk.transition(1)[2] ) );
  CHECK_THAT( 0.25, WithinRel( chunk.transition(1)[3] ) );
  CHECK_THAT(    2, WithinRel( chunk.transition(2)[0] ) );
  CHECK_THAT(    3, WithinRel( chunk.transition(2)[1] ) );
  CHECK_THAT(  2.5, WithinRel( chunk.transition(2)[2] ) );
  CHECK_THAT( 0.75, WithinRel( chunk.transition(2)[3] ) );
  CHECK_THAT(    3, WithinRel( chunk.transition(3)[0] ) );
  CHECK_THAT(    1, WithinRel( chunk.transition(3)[1] ) );
  CHECK_THAT(  5.5, WithinRel( chunk.transition(3)[2] ) );
  CHECK_THAT( 1.00, WithinRel( chunk.transition(3)[3] ) );

  CHECK(    1 == chunk.primaryDesignator(1) );
  CHECK(    0 == chunk.secondaryDesignator(1) );
  CHECK_THAT(  3.5, WithinRel( chunk.energy(1) ) );
  CHECK_THAT( 0.25, WithinRel( chunk.probability(1) ) );
  CHECK(    2 == chunk.primaryDesignator(2) );
  CHECK(    3 == chunk.secondaryDesignator(2) );
  CHECK_THAT(  2.5, WithinRel( chunk.energy(2) ) );
  CHECK_THAT( 0.75, WithinRel( chunk.probability(2) ) );
  CHECK(    3 == chunk.primaryDesignator(3) );
  CHECK(    1 == chunk.secondaryDesignator(3) );
  CHECK_THAT(  5.5, WithinRel( chunk.energy(3) ) );
  CHECK_THAT( 1.00, WithinRel( chunk.probability(3) ) );

  CHECK( true == chunk.isRadiativeTransition(1) );
  CHECK( false == chunk.isRadiativeTransition(2) );
  CHECK( false == chunk.isRadiativeTransition(3) );
}
