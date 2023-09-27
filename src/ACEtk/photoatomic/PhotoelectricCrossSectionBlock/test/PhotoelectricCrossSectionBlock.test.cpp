#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/photoatomic/PhotoelectricCrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PhotoelectricCrossSectionBlock = photoatomic::PhotoelectricCrossSectionBlock;

std::vector< double > chunk();
void verifyChunk( const PhotoelectricCrossSectionBlock& );

SCENARIO( "PhotoelectricCrossSectionBlock" ) {

  GIVEN( "valid data for a PhotoelectricCrossSectionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< std::vector< double > > photoelectric = {

        {  1.,  2.,  3.,  4.,  5. },
        {  6.,  7.,  8.,  9., 10. },
        { 11., 12., 13., 14., 15. }
      };

      PhotoelectricCrossSectionBlock chunk( std::move( photoelectric ) );

      THEN( "a PhotoelectricCrossSectionBlock can be constructed and members can "
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

      PhotoelectricCrossSectionBlock chunk( xss.begin(), xss.end(), 3, 5 );

      THEN( "a PhotoelectricCrossSectionBlock can be constructed and members can "
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

  return {

     1.,  2.,  3.,  4.,  5.,
     6.,  7.,  8.,  9., 10.,
    11., 12., 13., 14., 15.
  };
}

void verifyChunk( const PhotoelectricCrossSectionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 15 == chunk.length() );
  CHECK( "SPHEL" == chunk.name() );

  CHECK( 15 == chunk.XSS().size() );

  CHECK( 5 == chunk.NES() );
  CHECK( 5 == chunk.numberEnergyPoints() );
  CHECK( 3 == chunk.NSSH() );
  CHECK( 3 == chunk.numberElectronSubshells() );

  CHECK( 5 == chunk.photoelectric(1).size() );
  CHECK( 5 == chunk.photoelectric(2).size() );
  CHECK( 5 == chunk.photoelectric(3).size() );

  CHECK(   1. == Approx( chunk.photoelectric(1)[0] ) );
  CHECK(   2. == Approx( chunk.photoelectric(1)[1] ) );
  CHECK(   3. == Approx( chunk.photoelectric(1)[2] ) );
  CHECK(   4. == Approx( chunk.photoelectric(1)[3] ) );
  CHECK(   5. == Approx( chunk.photoelectric(1)[4] ) );
  CHECK(   6. == Approx( chunk.photoelectric(2)[0] ) );
  CHECK(   7. == Approx( chunk.photoelectric(2)[1] ) );
  CHECK(   8. == Approx( chunk.photoelectric(2)[2] ) );
  CHECK(   9. == Approx( chunk.photoelectric(2)[3] ) );
  CHECK(  10. == Approx( chunk.photoelectric(2)[4] ) );
  CHECK(  11. == Approx( chunk.photoelectric(3)[0] ) );
  CHECK(  12. == Approx( chunk.photoelectric(3)[1] ) );
  CHECK(  13. == Approx( chunk.photoelectric(3)[2] ) );
  CHECK(  14. == Approx( chunk.photoelectric(3)[3] ) );
  CHECK(  15. == Approx( chunk.photoelectric(3)[4] ) );
}
