// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/SubshellTransitionDataBlock.hpp"

// other includes
#include "ACEtk/fromFile.hpp"

// convenience typedefs
using namespace njoy::ACEtk;
using SubshellTransitionDataBlock = electron::SubshellTransitionDataBlock;
using SubshellTransitionData = electron::SubshellTransitionData;

std::vector< double > chunk();
void verifyChunk( const SubshellTransitionDataBlock& );

SCENARIO( "SubshellTransitionDataBlock" ) {

  GIVEN( "valid data for a SubshellTransitionDataBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< SubshellTransitionData > transitions = {

        SubshellTransitionData( { 1, 2, 3 }, { 0, 3, 1 },
                                { 3.5, 2.5, 5.5 }, { 0.25, 0.75, 1. } ),
        SubshellTransitionData(),
        SubshellTransitionData(),
        SubshellTransitionData()
      };

      SubshellTransitionDataBlock chunk( std::move( transitions ) );

      THEN( "a SubshellTransitionDataBlock can be constructed and "
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

      SubshellTransitionDataBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 4 );

      THEN( "a SubshellTransitionDataBlock can be constructed and "
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

  return { 0, 12, 12, 12,
           1, 0, 3.5, 0.25, 2, 3, 2.5, 0.75, 3, 1, 5.5, 1.00 };
}

void verifyChunk( const SubshellTransitionDataBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 16 == chunk.length() );
  CHECK( "XPROB" == chunk.name() );

  CHECK( 4 == chunk.NSSH() );
  CHECK( 4 == chunk.numberElectronSubshells() );
  CHECK( 4 == chunk.data().size() );

  CHECK(  1 == chunk.LTRAN(1) );
  CHECK( 13 == chunk.LTRAN(2) );
  CHECK( 13 == chunk.LTRAN(3) );
  CHECK( 13 == chunk.LTRAN(4) );
  CHECK(  1 == chunk.transitionDataLocator(1) );
  CHECK( 13 == chunk.transitionDataLocator(2) );
  CHECK( 13 == chunk.transitionDataLocator(3) );
  CHECK( 13 == chunk.transitionDataLocator(4) );

  auto xs = chunk.transitionData(1);

  CHECK( 3 == xs.NT() );
  CHECK( 3 == xs.numberTransitions() );

  CHECK( 4 == xs.transition(1).size() );
  CHECK( 4 == xs.transition(2).size() );
  CHECK( 4 == xs.transition(3).size() );

  CHECK_THAT(    1, WithinRel( xs.transition(1)[0] ) );
  CHECK_THAT(    0, WithinRel( xs.transition(1)[1] ) );
  CHECK_THAT(  3.5, WithinRel( xs.transition(1)[2] ) );
  CHECK_THAT( 0.25, WithinRel( xs.transition(1)[3] ) );
  CHECK_THAT(    2, WithinRel( xs.transition(2)[0] ) );
  CHECK_THAT(    3, WithinRel( xs.transition(2)[1] ) );
  CHECK_THAT(  2.5, WithinRel( xs.transition(2)[2] ) );
  CHECK_THAT( 0.75, WithinRel( xs.transition(2)[3] ) );
  CHECK_THAT(    3, WithinRel( xs.transition(3)[0] ) );
  CHECK_THAT(    1, WithinRel( xs.transition(3)[1] ) );
  CHECK_THAT(  5.5, WithinRel( xs.transition(3)[2] ) );
  CHECK_THAT( 1.00, WithinRel( xs.transition(3)[3] ) );

  CHECK(    1 == xs.primaryDesignator(1) );
  CHECK(    0 == xs.secondaryDesignator(1) );
  CHECK_THAT(  3.5, WithinRel( xs.energy(1) ) );
  CHECK_THAT( 0.25, WithinRel( xs.probability(1) ) );
  CHECK(    2 == xs.primaryDesignator(2) );
  CHECK(    3 == xs.secondaryDesignator(2) );
  CHECK_THAT(  2.5, WithinRel( xs.energy(2) ) );
  CHECK_THAT( 0.75, WithinRel( xs.probability(2) ) );
  CHECK(    3 == xs.primaryDesignator(3) );
  CHECK(    1 == xs.secondaryDesignator(3) );
  CHECK_THAT(  5.5, WithinRel( xs.energy(3) ) );
  CHECK_THAT( 1.00, WithinRel( xs.probability(3) ) );

  CHECK( true == xs.isRadiativeTransition(1) );
  CHECK( false == xs.isRadiativeTransition(2) );
  CHECK( false == xs.isRadiativeTransition(3) );

  xs = chunk.transitionData(2);

  CHECK( 0 == xs.NT() );
  CHECK( 0 == xs.numberTransitions() );

  xs = chunk.transitionData(3);

  CHECK( 0 == xs.NT() );
  CHECK( 0 == xs.numberTransitions() );

  xs = chunk.data()[0];

  CHECK( 3 == xs.NT() );
  CHECK( 3 == xs.numberTransitions() );

  CHECK( 4 == xs.transition(1).size() );
  CHECK( 4 == xs.transition(2).size() );
  CHECK( 4 == xs.transition(3).size() );

  CHECK_THAT(    1, WithinRel( xs.transition(1)[0] ) );
  CHECK_THAT(    0, WithinRel( xs.transition(1)[1] ) );
  CHECK_THAT(  3.5, WithinRel( xs.transition(1)[2] ) );
  CHECK_THAT( 0.25, WithinRel( xs.transition(1)[3] ) );
  CHECK_THAT(    2, WithinRel( xs.transition(2)[0] ) );
  CHECK_THAT(    3, WithinRel( xs.transition(2)[1] ) );
  CHECK_THAT(  2.5, WithinRel( xs.transition(2)[2] ) );
  CHECK_THAT( 0.75, WithinRel( xs.transition(2)[3] ) );
  CHECK_THAT(    3, WithinRel( xs.transition(3)[0] ) );
  CHECK_THAT(    1, WithinRel( xs.transition(3)[1] ) );
  CHECK_THAT(  5.5, WithinRel( xs.transition(3)[2] ) );
  CHECK_THAT( 1.00, WithinRel( xs.transition(3)[3] ) );

  CHECK(    1 == xs.primaryDesignator(1) );
  CHECK(    0 == xs.secondaryDesignator(1) );
  CHECK_THAT(  3.5, WithinRel( xs.energy(1) ) );
  CHECK_THAT( 0.25, WithinRel( xs.probability(1) ) );
  CHECK(    2 == xs.primaryDesignator(2) );
  CHECK(    3 == xs.secondaryDesignator(2) );
  CHECK_THAT(  2.5, WithinRel( xs.energy(2) ) );
  CHECK_THAT( 0.75, WithinRel( xs.probability(2) ) );
  CHECK(    3 == xs.primaryDesignator(3) );
  CHECK(    1 == xs.secondaryDesignator(3) );
  CHECK_THAT(  5.5, WithinRel( xs.energy(3) ) );
  CHECK_THAT( 1.00, WithinRel( xs.probability(3) ) );

  CHECK( true == xs.isRadiativeTransition(1) );
  CHECK( false == xs.isRadiativeTransition(2) );
  CHECK( false == xs.isRadiativeTransition(3) );

  xs = chunk.data()[1];

  CHECK( 0 == xs.NT() );
  CHECK( 0 == xs.numberTransitions() );

  xs = chunk.data()[2];

  CHECK( 0 == xs.NT() );
  CHECK( 0 == xs.numberTransitions() );
}
