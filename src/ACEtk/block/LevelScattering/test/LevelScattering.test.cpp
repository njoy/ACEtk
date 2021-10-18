#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/LevelScattering.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using LevelScattering = block::LevelScattering;

std::vector< double > chunk();
void verifyChunk( const LevelScattering& );

SCENARIO( "LevelScattering" ) {

  GIVEN( "valid data for a LevelScattering instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double c1 = 7.712958e-05;
      double c2 = .9914722;

      LevelScattering chunk( c1, c2 );

      THEN( "a LevelScattering can be constructed and members can "
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

      LevelScattering chunk( xss.begin(), xss.end() );

      THEN( "a LevelScattering can be constructed and members can "
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

  return { 7.71295800000E-05,   9.91472200000E-01 };
}

void verifyChunk( const LevelScattering& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 2 == chunk.length() );
  CHECK( "DLW::LevelScattering" == chunk.name() );

  CHECK( 7.71295800000E-05 == Approx( chunk.C1() ) );
  CHECK( .9914722 == Approx( chunk.C2() ) );
}
