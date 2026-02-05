// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/FissionChiDataBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using FissionChiDataBlock = multigroup::FissionChiDataBlock;

std::vector< double > chunk();
void verifyChunk( const FissionChiDataBlock&, const std::vector< double >& );

SCENARIO( "FissionChiDataBlock" ) {

  GIVEN( "valid data for a FissionChiDataBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > pfns = {

  3.227570000000E-05,  7.312440000000E-05,  2.343740000000E-04,  1.240120000000E-03,
  6.713940000000E-03,  2.068860000000E-02,  1.217780000000E-01,  1.038050000000E-01,
  1.194360000000E-01,  1.214190000000E-01,  1.115690000000E-01,  1.706130000000E-01,
  1.047060000000E-01,  5.813530000000E-02,  3.017230000000E-02,  2.257480000000E-02,
  5.273470000000E-03,  1.190540000000E-03,  2.672500000000E-04,  5.953610000000E-05,
  1.335350000000E-05,  2.976410000000E-06,  6.642330000000E-07,  1.480150000000E-07,
  3.305130000000E-08,  7.385720000000E-09,  1.644490000000E-09,  3.702850000000E-10,
  8.187100000000E-11,  2.337520000000E-11
      };
      

      FissionChiDataBlock chunk( std::move( pfns ) );

      THEN( "a FissionChiDataBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      FissionChiDataBlock chunk( xss.begin(), xss.end(), 30 );

      THEN( "a FissionChiDataBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      FissionChiDataBlock chunk( xss.begin(), xss.end(), 30 );
      FissionChiDataBlock copy( chunk );

      THEN( "an FissionChiDataBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      FissionChiDataBlock chunk( xss.begin(), xss.end(), 30 );
      FissionChiDataBlock move( std::move( chunk ) );

      THEN( "an FissionChiDataBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

  3.227570000000E-05,  7.312440000000E-05,  2.343740000000E-04,  1.240120000000E-03,
  6.713940000000E-03,  2.068860000000E-02,  1.217780000000E-01,  1.038050000000E-01,
  1.194360000000E-01,  1.214190000000E-01,  1.115690000000E-01,  1.706130000000E-01,
  1.047060000000E-01,  5.813530000000E-02,  3.017230000000E-02,  2.257480000000E-02,
  5.273470000000E-03,  1.190540000000E-03,  2.672500000000E-04,  5.953610000000E-05,
  1.335350000000E-05,  2.976410000000E-06,  6.642330000000E-07,  1.480150000000E-07,
  3.305130000000E-08,  7.385720000000E-09,  1.644490000000E-09,  3.702850000000E-10,
  8.187100000000E-11,  2.337520000000E-11
  };
}

void verifyChunk( const FissionChiDataBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 30 == chunk.length() );
  CHECK( "CHI" == chunk.name() );

  CHECK( 30 == chunk.XSS().size() );

  CHECK( 30 == chunk.fissionFraction().size() );

  CHECK_THAT( 3.227570000000E-05, WithinRel( chunk.fissionFraction().front() ) );
  CHECK_THAT( 2.337520000000E-11, WithinRel( chunk.fissionFraction().back() ) );
}
