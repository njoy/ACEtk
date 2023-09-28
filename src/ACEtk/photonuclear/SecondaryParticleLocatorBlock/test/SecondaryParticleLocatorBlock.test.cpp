#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/photonuclear/SecondaryParticleLocatorBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using SecondaryParticleLocatorBlock = photonuclear::SecondaryParticleLocatorBlock;

std::vector< double > chunk();
void verifyChunk( const SecondaryParticleLocatorBlock& );

SCENARIO( "SecondaryParticleLocatorBlock" ) {

  GIVEN( "valid data for a SecondaryParticleLocatorBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< unsigned int > types = {

        1, 2, 9, 31, 32, 33, 34
      };
      std::vector< unsigned int > numbers = {

        2, 1, 1, 1, 1, 1, 1
      };
      std::vector< std::array< unsigned int, 10 > > locators = {

        { 543,                 635,                 727,                 729,
          731,                 733,                1085,                1087,
          1087,                1089 },
        { 198198,              198290,              198382,              198383,
          198384,              198385,              198569,              198570,
          198570,              198571 },
        { 282208,              282288,              282368,              282369,
          282370,              282371,              282543,              282544,
          282544,              282545 },
        { 428550,              428623,              428696,              428697,
          428698,              428699,              428869,              428870,
          428870,              428871 },
        { 575293,              575364,              575435,              575436,
          575437,              575438,              575604,              575605,
          575605,              575606 },
        { 719700,              719769,              719838,              719839,
          719840,              719841,              720009,              720010,
          720010,              720011 },
        { 863286,              863378,              863470,              863471,
          863472,              863473,              863657,              863658,
          863658,              863659 }
      };

      SecondaryParticleLocatorBlock chunk( std::move( types ),
                                                       std::move( numbers ),
                                                       std::move( locators ) );

      THEN( "a SecondaryParticleLocatorBlock can be constructed and members "
            "can be tested" ) {

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

      SecondaryParticleLocatorBlock chunk( xss.begin(), xss.end(), 7 );

      THEN( "a SecondaryParticleLocatorBlock can be constructed and members "
            "can be tested" ) {

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

  return {

                                                   1,                   2,
       543,                 635,                 727,                 729,
       731,                 733,                1085,                1087,
      1087,                1089,                   2,                   1,
    198198,              198290,              198382,              198383,
    198384,              198385,              198569,              198570,
    198570,              198571,                   9,                   1,
    282208,              282288,              282368,              282369,
    282370,              282371,              282543,              282544,
    282544,              282545,                  31,                   1,
    428550,              428623,              428696,              428697,
    428698,              428699,              428869,              428870,
    428870,              428871,                  32,                   1,
    575293,              575364,              575435,              575436,
    575437,              575438,              575604,              575605,
    575605,              575606,                  33,                   1,
    719700,              719769,              719838,              719839,
    719840,              719841,              720009,              720010,
    720010,              720011,                  34,                   1,
    863286,              863378,              863470,              863471,
    863472,              863473,              863657,              863658,
    863658,              863659
  };
}

void verifyChunk( const SecondaryParticleLocatorBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 84 == chunk.length() );
  CHECK( "IXSU" == chunk.name() );

  CHECK( 7 == chunk.NTYPE() );
  CHECK( 7 == chunk.numberAdditionalSecondaryParticleTypes() );

  CHECK( 1 == chunk.IP( 1 ) );
  CHECK( 2 == chunk.IP( 2 ) );
  CHECK( 9 == chunk.IP( 3 ) );
  CHECK( 31 == chunk.IP( 4 ) );
  CHECK( 32 == chunk.IP( 5 ) );
  CHECK( 33 == chunk.IP( 6 ) );
  CHECK( 34 == chunk.IP( 7 ) );

  CHECK( 2 == chunk.NP( 1 ) );
  CHECK( 1 == chunk.NP( 2 ) );
  CHECK( 1 == chunk.NP( 3 ) );
  CHECK( 1 == chunk.NP( 4 ) );
  CHECK( 1 == chunk.NP( 5 ) );
  CHECK( 1 == chunk.NP( 6 ) );
  CHECK( 1 == chunk.NP( 7 ) );

  CHECK( 543 == chunk.PXS( 1 ) );
  CHECK( 635 == chunk.PHN( 1 ) );
  CHECK( 727 == chunk.MTRH( 1 ) );
  CHECK( 729 == chunk.TYRH( 1 ) );
  CHECK( 731 == chunk.LSIGH( 1 ) );
  CHECK( 733 == chunk.SIGH( 1 ) );
  CHECK( 1085 == chunk.LANDH( 1 ) );
  CHECK( 1087 == chunk.ANDH( 1 ) );
  CHECK( 1087 == chunk.LDLWH( 1 ) );
  CHECK( 1089 == chunk.DLWH( 1 ) );

  CHECK( 863286 == chunk.PXS( 7 ) );
  CHECK( 863378 == chunk.PHN( 7 ) );
  CHECK( 863470 == chunk.MTRH( 7 ) );
  CHECK( 863471 == chunk.TYRH( 7 ) );
  CHECK( 863472 == chunk.LSIGH( 7 ) );
  CHECK( 863473 == chunk.SIGH( 7 ) );
  CHECK( 863657 == chunk.LANDH( 7 ) );
  CHECK( 863658 == chunk.ANDH( 7 ) );
  CHECK( 863658 == chunk.LDLWH( 7 ) );
  CHECK( 863659 == chunk.DLWH( 7 ) );
}
