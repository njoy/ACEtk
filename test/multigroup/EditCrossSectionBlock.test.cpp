// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/EditCrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EditCrossSectionBlock = multigroup::EditCrossSectionBlock;

std::vector< double > chunk();
void verifyChunk( const EditCrossSectionBlock&, const std::vector< double >& );
EditCrossSectionBlock makeDummyBlock();

SCENARIO( "EditCrossSectionBlock" ) {

  GIVEN( "valid data for an EditCrossSectionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< std::vector< double > > values = {
        
        {  6.199930000000E-01,  6.907610000000E-01,  7.469720000000E-01,  8.664520000000E-01,
           1.065010000000E+00,  1.302860000000E+00,  1.764430000000E+00,  2.198580000000E+00,
           2.559500000000E+00,  2.953190000000E+00,  3.399330000000E+00,  4.156230000000E+00,
           5.377230000000E+00,  6.951270000000E+00,  8.974890000000E+00,  1.228050000000E+01,
           1.619280000000E+01,  1.860520000000E+01,  1.972630000000E+01,  2.018420000000E+01,
           2.035910000000E+01,  2.042520000000E+01,  2.044970000000E+01,  2.045650000000E+01,
           2.046930000000E+01,  2.050430000000E+01,  2.059860000000E+01,  2.085680000000E+01,
           2.155870000000E+01,  2.942240000000E+01 },
        {  2.847090000000E-05,  2.976620000000E-05,  3.032220000000E-05,  3.180660000000E-05,  
           3.349790000000E-05,  3.524820000000E-05,  3.623040000000E-05,  3.579650000000E-05,  
           3.497190000000E-05,  3.431090000000E-05,  3.433360000000E-05,  3.451760000000E-05,  
           3.622100000000E-05,  4.202520000000E-05,  5.677600000000E-05,  1.012830000000E-04,  
           2.061770000000E-04,  3.949250000000E-04,  7.082510000000E-04,  1.195170000000E-03,  
           1.947160000000E-03,  3.217480000000E-03,  5.321480000000E-03,  8.793070000000E-03,  
           1.449130000000E-02,  2.391300000000E-02,  3.934770000000E-02,  6.495030000000E-02,  
           1.071560000000E-01,  3.011490000000E-01 },
        {  2.847090000000E-05,  2.976620000000E-05,  3.032220000000E-05,  3.180660000000E-05,
           3.349790000000E-05,  3.524820000000E-05,  3.623040000000E-05,  3.579650000000E-05,
           3.497190000000E-05,  3.431090000000E-05,  3.433360000000E-05,  3.451760000000E-05,
           3.622100000000E-05,  4.202520000000E-05,  5.677600000000E-05,  1.012830000000E-04,
           2.061770000000E-04,  3.949250000000E-04,  7.082510000000E-04,  1.195170000000E-03,
           1.947160000000E-03,  3.217480000000E-03,  5.321480000000E-03,  8.793070000000E-03,
           1.449130000000E-02,  2.391300000000E-02,  3.934770000000E-02,  6.495030000000E-02,
           1.071560000000E-01,  3.011490000000E-01 },
        {  2.847090000000E-05,  2.976620000000E-05,  3.032220000000E-05,  3.180660000000E-05,  
           3.349790000000E-05,  3.524820000000E-05,  3.623040000000E-05,  3.579650000000E-05,  
           3.497190000000E-05,  3.431090000000E-05,  3.433360000000E-05,  3.451760000000E-05,  
           3.622100000000E-05,  4.202520000000E-05,  5.677600000000E-05,  1.012830000000E-04,  
           2.061770000000E-04,  3.949250000000E-04,  7.082510000000E-04,  1.195170000000E-03,  
           1.947160000000E-03,  3.217480000000E-03,  5.321480000000E-03,  8.793070000000E-03,  
           1.449130000000E-02,  2.391300000000E-02,  3.934770000000E-02,  6.495030000000E-02,  
           1.071560000000E-01,  3.011490000000E-01 }
      };

      EditCrossSectionBlock chunk( std::move( values ) );

      THEN( "an EditCrossSectionBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
    WHEN( "the data is defined by iterators" ) {

      EditCrossSectionBlock chunk( xss.begin(), xss.end(), 4 );

      THEN( "an EditCrossSectionBlock can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      EditCrossSectionBlock chunk( xss.begin(), xss.end(), 4 );
      EditCrossSectionBlock copy( chunk );

      THEN( "an EditCrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      EditCrossSectionBlock chunk( xss.begin(), xss.end(), 4 );
      EditCrossSectionBlock move( std::move( chunk ) );

      THEN( "an EditCrossSectionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      EditCrossSectionBlock chunk( xss.begin(), xss.end(), 4 );
      EditCrossSectionBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an EditCrossSectionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      EditCrossSectionBlock chunk( xss.begin(), xss.end(), 4 );
      EditCrossSectionBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an EditCrossSectionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

    return  { 30,
           6.199930000000E-01,  6.907610000000E-01,  7.469720000000E-01,  8.664520000000E-01,
           1.065010000000E+00,  1.302860000000E+00,  1.764430000000E+00,  2.198580000000E+00,
           2.559500000000E+00,  2.953190000000E+00,  3.399330000000E+00,  4.156230000000E+00,
           5.377230000000E+00,  6.951270000000E+00,  8.974890000000E+00,  1.228050000000E+01,
           1.619280000000E+01,  1.860520000000E+01,  1.972630000000E+01,  2.018420000000E+01,
           2.035910000000E+01,  2.042520000000E+01,  2.044970000000E+01,  2.045650000000E+01,
           2.046930000000E+01,  2.050430000000E+01,  2.059860000000E+01,  2.085680000000E+01,
           2.155870000000E+01,  2.942240000000E+01,
           2.847090000000E-05,  2.976620000000E-05,  3.032220000000E-05,  3.180660000000E-05,  
           3.349790000000E-05,  3.524820000000E-05,  3.623040000000E-05,  3.579650000000E-05,  
           3.497190000000E-05,  3.431090000000E-05,  3.433360000000E-05,  3.451760000000E-05,  
           3.622100000000E-05,  4.202520000000E-05,  5.677600000000E-05,  1.012830000000E-04,  
           2.061770000000E-04,  3.949250000000E-04,  7.082510000000E-04,  1.195170000000E-03,  
           1.947160000000E-03,  3.217480000000E-03,  5.321480000000E-03,  8.793070000000E-03,  
           1.449130000000E-02,  2.391300000000E-02,  3.934770000000E-02,  6.495030000000E-02,  
           1.071560000000E-01,  3.011490000000E-01,
           2.847090000000E-05,  2.976620000000E-05,  3.032220000000E-05,  3.180660000000E-05,
           3.349790000000E-05,  3.524820000000E-05,  3.623040000000E-05,  3.579650000000E-05,
           3.497190000000E-05,  3.431090000000E-05,  3.433360000000E-05,  3.451760000000E-05,
           3.622100000000E-05,  4.202520000000E-05,  5.677600000000E-05,  1.012830000000E-04,
           2.061770000000E-04,  3.949250000000E-04,  7.082510000000E-04,  1.195170000000E-03,
           1.947160000000E-03,  3.217480000000E-03,  5.321480000000E-03,  8.793070000000E-03,
           1.449130000000E-02,  2.391300000000E-02,  3.934770000000E-02,  6.495030000000E-02,
           1.071560000000E-01,  3.011490000000E-01,
           2.847090000000E-05,  2.976620000000E-05,  3.032220000000E-05,  3.180660000000E-05,  
           3.349790000000E-05,  3.524820000000E-05,  3.623040000000E-05,  3.579650000000E-05,  
           3.497190000000E-05,  3.431090000000E-05,  3.433360000000E-05,  3.451760000000E-05,  
           3.622100000000E-05,  4.202520000000E-05,  5.677600000000E-05,  1.012830000000E-04,  
           2.061770000000E-04,  3.949250000000E-04,  7.082510000000E-04,  1.195170000000E-03,  
           1.947160000000E-03,  3.217480000000E-03,  5.321480000000E-03,  8.793070000000E-03,  
           1.449130000000E-02,  2.391300000000E-02,  3.934770000000E-02,  6.495030000000E-02,  
           1.071560000000E-01,  3.011490000000E-01 };
    }

void verifyChunk( const EditCrossSectionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 121 == chunk.length() );
  CHECK( "XSED" == chunk.name() );

  CHECK( 30 == chunk.NGRP() );
  CHECK( 30 == chunk.numberEnergyGroups() );

  CHECK( 4 == chunk.NEDIT() );
  CHECK( 4 == chunk.numberEditReactions() );

  CHECK_THAT( 6.199930000000E-01, WithinRel( chunk.C( 1 ).front() ) );
  CHECK_THAT( 6.199930000000E-01, WithinRel( chunk.column( 1 ).front() ) );
  CHECK_THAT( 2.942240000000E+01, WithinRel( chunk.C( 1 ).back() ) );
  CHECK_THAT( 2.942240000000E+01, WithinRel( chunk.column( 1 ).back() ) );

  CHECK_THAT( 2.847090000000E-05, WithinRel( chunk.C( 2 ).front() ) );
  CHECK_THAT( 2.847090000000E-05, WithinRel( chunk.column( 2 ).front() ) );
  CHECK_THAT( 3.011490000000E-01, WithinRel( chunk.C( 2 ).back() ) );
  CHECK_THAT( 3.011490000000E-01, WithinRel( chunk.column( 2 ).back() ) );

  CHECK_THAT( 2.847090000000E-05, WithinRel( chunk.C( 3 ).front() ) );
  CHECK_THAT( 2.847090000000E-05, WithinRel( chunk.column( 3 ).front() ) );
  CHECK_THAT( 3.011490000000E-01, WithinRel( chunk.C( 3 ).back() ) );
  CHECK_THAT( 3.011490000000E-01, WithinRel( chunk.column( 3 ).back() ) );

  CHECK_THAT( 2.847090000000E-05, WithinRel( chunk.C( 4 ).front() ) );
  CHECK_THAT( 2.847090000000E-05, WithinRel( chunk.column( 4 ).front() ) );
  CHECK_THAT( 3.011490000000E-01, WithinRel( chunk.C( 4 ).back() ) );
  CHECK_THAT( 3.011490000000E-01, WithinRel( chunk.column( 4 ).back() ) );

  CHECK_THROWS( chunk.column( 7 ) );

}

EditCrossSectionBlock makeDummyBlock() {

  return { { { 2 }, { 2 } } };
}
