// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/FissionCrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using FissionCrossSectionBlock = multigroup::FissionCrossSectionBlock;

std::vector< double > chunk();
void verifyChunk( const FissionCrossSectionBlock&, const std::vector< double >& );

SCENARIO( "FissionCrossSectionBlock" ) {

  GIVEN( "valid data for a FissionCrossSectionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > fission = {

             2.847090000000E-05,  2.976620000000E-05,
             3.032220000000E-05,  3.180660000000E-05,  3.349790000000E-05,  3.524820000000E-05,
             3.623040000000E-05,  3.579650000000E-05,  3.497190000000E-05,  3.431090000000E-05,
             3.433360000000E-05,  3.451760000000E-05,  3.622100000000E-05,  4.202520000000E-05,
             5.677600000000E-05,  1.012830000000E-04,  2.061770000000E-04,  3.949250000000E-04,
             7.082510000000E-04,  1.195170000000E-03,  1.947160000000E-03,  3.217480000000E-03,
             5.321480000000E-03,  8.793070000000E-03,  1.449130000000E-02,  2.391300000000E-02,
             3.934770000000E-02,  6.495030000000E-02,  1.071560000000E-01,  3.011490000000E-01
      };
      

      FissionCrossSectionBlock chunk( std::move( fission ) );

      THEN( "a FissionCrossSectionBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      FissionCrossSectionBlock chunk( xss.begin(), xss.end(), 30 );

      THEN( "a FissionCrossSectionBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      FissionCrossSectionBlock chunk( xss.begin(), xss.end(), 30 );
      FissionCrossSectionBlock copy( chunk );

      THEN( "an FissionCrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      FissionCrossSectionBlock chunk( xss.begin(), xss.end(), 30 );
      FissionCrossSectionBlock move( std::move( chunk ) );

      THEN( "an FissionCrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

             2.847090000000E-05,  2.976620000000E-05,
             3.032220000000E-05,  3.180660000000E-05,  3.349790000000E-05,  3.524820000000E-05,
             3.623040000000E-05,  3.579650000000E-05,  3.497190000000E-05,  3.431090000000E-05,
             3.433360000000E-05,  3.451760000000E-05,  3.622100000000E-05,  4.202520000000E-05,
             5.677600000000E-05,  1.012830000000E-04,  2.061770000000E-04,  3.949250000000E-04,
             7.082510000000E-04,  1.195170000000E-03,  1.947160000000E-03,  3.217480000000E-03,
             5.321480000000E-03,  8.793070000000E-03,  1.449130000000E-02,  2.391300000000E-02,
             3.934770000000E-02,  6.495030000000E-02,  1.071560000000E-01,  3.011490000000E-01
  };
}

void verifyChunk( const FissionCrossSectionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 30 == chunk.length() );
  CHECK( "FISS" == chunk.name() );

  CHECK( 30 == chunk.XSS().size() );

  CHECK( 30 == chunk.fissionCrossSection().size() );

  CHECK_THAT( 2.847090000000E-05, WithinRel( chunk.fissionCrossSection().front() ) );
  CHECK_THAT( 3.011490000000E-01, WithinRel( chunk.fissionCrossSection().back() ) );
}
