// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/photoatomic/PhotoelectricCrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PhotoelectricCrossSectionBlock = photoatomic::PhotoelectricCrossSectionBlock;

std::vector< double > chunk();
void verifyChunk( const PhotoelectricCrossSectionBlock&, const std::vector< double >& );
PhotoelectricCrossSectionBlock makeDummyBlock();

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

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      PhotoelectricCrossSectionBlock chunk( xss.begin(), xss.end(), 3, 5 );

      THEN( "a PhotoelectricCrossSectionBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
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

void verifyChunk( const PhotoelectricCrossSectionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

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

  CHECK_THAT(   1., WithinRel( chunk.photoelectric(1)[0] ) );
  CHECK_THAT(   2., WithinRel( chunk.photoelectric(1)[1] ) );
  CHECK_THAT(   3., WithinRel( chunk.photoelectric(1)[2] ) );
  CHECK_THAT(   4., WithinRel( chunk.photoelectric(1)[3] ) );
  CHECK_THAT(   5., WithinRel( chunk.photoelectric(1)[4] ) );
  CHECK_THAT(   6., WithinRel( chunk.photoelectric(2)[0] ) );
  CHECK_THAT(   7., WithinRel( chunk.photoelectric(2)[1] ) );
  CHECK_THAT(   8., WithinRel( chunk.photoelectric(2)[2] ) );
  CHECK_THAT(   9., WithinRel( chunk.photoelectric(2)[3] ) );
  CHECK_THAT(  10., WithinRel( chunk.photoelectric(2)[4] ) );
  CHECK_THAT(  11., WithinRel( chunk.photoelectric(3)[0] ) );
  CHECK_THAT(  12., WithinRel( chunk.photoelectric(3)[1] ) );
  CHECK_THAT(  13., WithinRel( chunk.photoelectric(3)[2] ) );
  CHECK_THAT(  14., WithinRel( chunk.photoelectric(3)[3] ) );
  CHECK_THAT(  15., WithinRel( chunk.photoelectric(3)[4] ) );
}
