// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/BandP0Data.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using BandP0Data = multigroup::BandP0Data;

std::vector< double > chunk();
void verifyChunk( const BandP0Data&, std::vector< double >&);
BandP0Data makeDummyBlock();

SCENARIO( "BandP0Data" ) {

  GIVEN( "valid data for a BandP0Data instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

        std::vector < std::vector < double > > values = {
            { 2., 3., 4., 0. },
            { 1., 2., 3., 4. },
            { 0., 1., 2., 3. },
            { 0., 0., 1., 2. }
        };

        BandP0Data chunk( std::move( values ), 2, 1 );


      THEN( "an BandP0Data can be constructed and "
            "members can be tested" ) {
            
          verifyChunk( chunk, xss );

      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      BandP0Data chunk( xss.begin(), xss.end(), 4, 2, 1 );

      THEN( "a BandP0Data can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the matrix has non-zero values outside the bands" ) {

        std::vector < std::vector < double > > badValues = {
            { 2., 3., 4., 6. },
            { 1., 2., 3., 4. },
            { 0., 1., 2., 3. },
            { 9., 0., 1., 2. }
        };

        BandP0Data chunk( std::move( badValues ), 2, 1 );


      THEN( "those values are thrown away" ) {
            
          verifyChunk( chunk, xss );

      } // THEN
    } // WHEN

  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

   return { 2., 3., 4., 1., 2., 3., 4., 1., 2., 3., 1., 2. };
}


void verifyChunk( const BandP0Data& chunk, std::vector< double >& xss ) {

    std::vector < std::vector < double > > ans = {
            { 2., 3., 4., 0. },
            { 1., 2., 3., 4. },
            { 0., 1., 2., 3. },
            { 0., 0., 1., 2. }
    };

// XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

// interface

  CHECK( 4 == chunk.NGRP() );
  CHECK( 4 == chunk.numberEnergyGroups() );

  CHECK( 2 == chunk.NDS() );
  CHECK( 2 == chunk.numberDownScatterGroups() );

  CHECK( 1 == chunk.NUS() );
  CHECK( 1 == chunk.numberUpScatterGroups() );

  CHECK( 12 == chunk.blockLength() );
  CHECK( 12 == chunk.length() );

  CHECK_THAT( 2., WithinRel( chunk.P0MatrixList()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.P0MatrixList()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.P0MatrixList()[2] ) );

  CHECK_THAT( 1., WithinRel( chunk.P0MatrixList()[3] ) );
  CHECK_THAT( 2., WithinRel( chunk.P0MatrixList()[4] ) );
  CHECK_THAT( 3., WithinRel( chunk.P0MatrixList()[5] ) );
  CHECK_THAT( 4., WithinRel( chunk.P0MatrixList()[6] ) );

  CHECK_THAT( 1., WithinRel( chunk.P0MatrixList()[7] ) );
  CHECK_THAT( 2., WithinRel( chunk.P0MatrixList()[8] ) );
  CHECK_THAT( 3., WithinRel( chunk.P0MatrixList()[9] ) );

  CHECK_THAT( 1., WithinRel( chunk.P0MatrixList()[10] ) );
  CHECK_THAT( 2., WithinRel( chunk.P0MatrixList()[11] ) );

  CHECK( 2 == chunk.groupDownScatterGroups( 1 ) );
  CHECK( 2 == chunk.groupDownScatterGroups( 2 ) );
  CHECK( 1 == chunk.groupDownScatterGroups( 3 ) );
  CHECK( 0 == chunk.groupDownScatterGroups( 4 ) );

  CHECK( 0 == chunk.groupUpScatterGroups( 1 ) );
  CHECK( 1 == chunk.groupUpScatterGroups( 2 ) );
  CHECK( 1 == chunk.groupUpScatterGroups( 3 ) );
  CHECK( 1 == chunk.groupUpScatterGroups( 4 ) );

  // row 1
  CHECK_THAT( 2., WithinRel( chunk.P0Value( 1, 1 ) ) );
  CHECK_THAT( 3., WithinRel( chunk.P0Value( 1, 2 ) ) );
  CHECK_THAT( 4., WithinRel( chunk.P0Value( 1, 3 ) ) );
  CHECK_THAT( 0., WithinRel( chunk.P0Value( 1, 4 ) ) );

  CHECK_THAT( 2., WithinRel( chunk.incidentRow( 1 ) [0] ) );
  CHECK_THAT( 3., WithinRel( chunk.incidentRow( 1 ) [1] ) );
  CHECK_THAT( 4., WithinRel( chunk.incidentRow( 1 ) [2] ) );
  CHECK_THAT( 0., WithinRel( chunk.incidentRow( 1 ) [3] ) );

  // row 2
  CHECK_THAT( 1., WithinRel( chunk.P0Value( 2, 1 ) ) );
  CHECK_THAT( 2., WithinRel( chunk.P0Value( 2, 2 ) ) );
  CHECK_THAT( 3., WithinRel( chunk.P0Value( 2, 3 ) ) );
  CHECK_THAT( 4., WithinRel( chunk.P0Value( 2, 4 ) ) );

  CHECK_THAT( 1., WithinRel( chunk.incidentRow( 2 )[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.incidentRow( 2 )[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.incidentRow( 2 )[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.incidentRow( 2 )[3] ) );

  // row 3
  CHECK_THAT( 0., WithinRel( chunk.P0Value( 3, 1 ) ) );
  CHECK_THAT( 1., WithinRel( chunk.P0Value( 3, 2 ) ) );
  CHECK_THAT( 2., WithinRel( chunk.P0Value( 3, 3 ) ) );
  CHECK_THAT( 3., WithinRel( chunk.P0Value( 3, 4 ) ) );

  CHECK( 4 == chunk.incidentRow( 3 ).size() );
  CHECK_THAT( 0., WithinRel( chunk.incidentRow( 3 )[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.incidentRow( 3 )[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.incidentRow( 3 )[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.incidentRow( 3 )[3] ) );

  // row 4
  CHECK_THAT( 0., WithinRel( chunk.P0Value( 4, 1 ) ) );
  CHECK_THAT( 0., WithinRel( chunk.P0Value( 4, 2 ) ) );
  CHECK_THAT( 1., WithinRel( chunk.P0Value( 4, 3 ) ) );
  CHECK_THAT( 2., WithinRel( chunk.P0Value( 4, 4 ) ) );

  CHECK( 4 == chunk.incidentRow( 4 ).size() );
  CHECK_THAT( 0., WithinRel( chunk.incidentRow( 4 )[0] ) );
  CHECK_THAT( 0., WithinRel( chunk.incidentRow( 4 )[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.incidentRow( 4 )[2] ) );
  CHECK_THAT( 2., WithinRel( chunk.incidentRow( 4 )[3] ) );

  auto mat = chunk.P0Matrix();
  for (unsigned int row = 1; row <= 4; ++row ){
    for (unsigned int col = 1; col <= 4; ++col ) {
      CHECK_THAT( ans[row-1][col-1], WithinRel( mat[row-1][col-1] ) );
    }
  }
}

