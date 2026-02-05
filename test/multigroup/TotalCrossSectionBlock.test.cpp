// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/TotalCrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TotalCrossSectionBlock = multigroup::TotalCrossSectionBlock;

std::vector< double > chunk();
void verifyChunk( const TotalCrossSectionBlock&, const std::vector< double >& );

SCENARIO( "TotalCrossSectionBlock" ) {

  GIVEN( "valid data for a TotalCrossSectionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > total = {

             6.200214709000E-01,  6.907907662000E-01,  7.470023222000E-01,  8.664838066000E-01,
             1.065043497900E+00,  1.302895248200E+00,  1.764466230400E+00,  2.198615796500E+00,
             2.559534971900E+00,  2.953224310900E+00,  3.399364333600E+00,  4.156264517600E+00,
             5.377266221000E+00,  6.951312025200E+00,  8.974946776000E+00,  1.228060128300E+01,
             1.619300617700E+01,  1.860559492500E+01,  1.972700825100E+01,  2.018539517000E+01,
             2.036104716000E+01,  2.042841748000E+01,  2.045502148000E+01,  2.046529307000E+01,
             2.048379130000E+01,  2.052821300000E+01,  2.063794770000E+01,  2.092175030000E+01,
             2.166585600000E+01,  2.972354900000E+01 
      };
      

      TotalCrossSectionBlock chunk( std::move( total ) );

      THEN( "a TotalCrossSectionBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      TotalCrossSectionBlock chunk( xss.begin(), xss.end(), 30 );

      THEN( "a TotalCrossSectionBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      TotalCrossSectionBlock chunk( xss.begin(), xss.end(), 30 );
      TotalCrossSectionBlock copy( chunk );

      THEN( "an TotalCrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      TotalCrossSectionBlock chunk( xss.begin(), xss.end(), 30 );
      TotalCrossSectionBlock move( std::move( chunk ) );

      THEN( "an TotalCrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

             6.200214709000E-01,  6.907907662000E-01,  7.470023222000E-01,  8.664838066000E-01,
             1.065043497900E+00,  1.302895248200E+00,  1.764466230400E+00,  2.198615796500E+00,
             2.559534971900E+00,  2.953224310900E+00,  3.399364333600E+00,  4.156264517600E+00,
             5.377266221000E+00,  6.951312025200E+00,  8.974946776000E+00,  1.228060128300E+01,
             1.619300617700E+01,  1.860559492500E+01,  1.972700825100E+01,  2.018539517000E+01,
             2.036104716000E+01,  2.042841748000E+01,  2.045502148000E+01,  2.046529307000E+01,
             2.048379130000E+01,  2.052821300000E+01,  2.063794770000E+01,  2.092175030000E+01,
             2.166585600000E+01,  2.972354900000E+01 
  };
}

void verifyChunk( const TotalCrossSectionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 30 == chunk.length() );
  CHECK( "TOT" == chunk.name() );

  CHECK( 30 == chunk.XSS().size() );

  CHECK( 30 == chunk.NGRP() );
  CHECK( 30 == chunk.numberEnergyGroups() );
  CHECK( 30 == chunk.totalCrossSection().size() );

  CHECK_THAT( 6.200214709000E-01, WithinRel( chunk.totalCrossSection().front() ) );
  CHECK_THAT( 2.972354900000E+01, WithinRel( chunk.totalCrossSection().back() ) );
}
