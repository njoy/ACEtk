// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/InterpolationData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using InterpolationData = continuous::InterpolationData;

std::vector< double > chunk();
void verifyChunk( const InterpolationData& );

SCENARIO( "InterpolationData" ) {

  GIVEN( "valid data for an InterpolationData instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > boundaries = { 5, 10 };
      std::vector< long > interpolants = { 1, 2 };

      InterpolationData chunk( "test",
                               std::move( boundaries ),
                               std::move( interpolants ) );

      THEN( "an InterpolationData can be constructed and members can be tested" ) {

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

      InterpolationData chunk( "test", xss.begin(), xss.end() );

      THEN( "an InterpolationData can be constructed and members can be tested" ) {

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

  return { 2, 5, 10, 1, 2 };
}

void verifyChunk( const InterpolationData& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 5 == chunk.length() );
  CHECK( "test" == chunk.name() );

  CHECK( 2 == chunk.NB() );
  CHECK( 2 == chunk.numberInterpolationRegions() );

  CHECK( false == chunk.isLinearLinear() );

  CHECK( 2 == chunk.INT().size() );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK( 2 == chunk.NBT().size() );
  CHECK( 2 == chunk.boundaries().size() );

  CHECK( 1 == chunk.INT()[0] );
  CHECK( 2 == chunk.INT()[1] );
  CHECK( 1 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.interpolants()[1] );
  CHECK(  5 == chunk.NBT()[0] );
  CHECK( 10 == chunk.NBT()[1] );
  CHECK(  5 == chunk.boundaries()[0] );
  CHECK( 10 == chunk.boundaries()[1] );
}
