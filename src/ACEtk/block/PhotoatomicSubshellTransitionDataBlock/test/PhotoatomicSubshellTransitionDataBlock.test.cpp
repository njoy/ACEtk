#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/PhotoatomicSubshellTransitionDataBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PhotoatomicSubshellTransitionDataBlock = block::PhotoatomicSubshellTransitionDataBlock;
using PhotoatomicSubshellTransitionData = block::PhotoatomicSubshellTransitionData;

std::vector< double > chunk();
void verifyChunk( const PhotoatomicSubshellTransitionDataBlock& );

SCENARIO( "PhotoatomicSubshellTransitionDataBlock" ) {

  GIVEN( "valid data for a PhotoatomicSubshellTransitionDataBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< PhotoatomicSubshellTransitionData > transitions = {

        PhotoatomicSubshellTransitionData( { 1, 2, 3 }, { 0, 3, 1 },
                                           { 3.5, 2.5, 5.5 }, { 0.25, 0.75, 1. } ),
        PhotoatomicSubshellTransitionData(),
        PhotoatomicSubshellTransitionData(),
        PhotoatomicSubshellTransitionData()
      };

      PhotoatomicSubshellTransitionDataBlock chunk( std::move( transitions ) );

      THEN( "a PhotoatomicSubshellTransitionDataBlock can be constructed and "
            "members can be tested" ) {

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

      PhotoatomicSubshellTransitionDataBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 4 );

      THEN( "a PhotoatomicSubshellTransitionDataBlock can be constructed and "
            "members can be tested" ) {

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

  return { 0, 12, 12, 12,
           1, 0, 3.5, 0.25, 2, 3, 2.5, 0.75, 3, 1, 5.5, 1.00 };
}

void verifyChunk( const PhotoatomicSubshellTransitionDataBlock& chunk ) {

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

  xs = chunk.transitionData(2);

  xs = chunk.transitionData(3);

  xs = chunk.data()[0];

  xs = chunk.data()[1];

  xs = chunk.data()[2];
}
