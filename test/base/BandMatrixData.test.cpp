// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/base/BandMatrixData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using BandMatrixData = base::BandMatrixData;

std::vector< double > chunk();
void verifyChunk( const BandMatrixData&, std::vector< double >&);
BandMatrixData makeDummyBlock();

SCENARIO( "BandMatrixData" ) {

  GIVEN( "valid data for an BandMatrixData instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

        std::vector < std::vector < double > > values = {
            { 2., 3., 4., 0. },
            { 1., 2., 3., 4. },
            { 0., 1., 2., 3. },
            { 0., 0., 1., 2. }
        };

        BandMatrixData chunk( "Band", std::move( values ), 2, 1 );


      THEN( "an BandMatrixData can be constructed and "
            "members can be tested" ) {
            
          verifyChunk( chunk, xss );

      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      BandMatrixData chunk( "Band", xss.begin(), xss.end(), 4, 2, 1 );

      THEN( "a BandMatrixData can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

   return { 2., 3., 4., 1., 2., 3., 4., 1., 2., 3., 1., 2. };
}

void verifyChunk( const BandMatrixData& chunk, std::vector< double >& xss ) {

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

  CHECK( 4 == chunk.size() );
  CHECK( 4 == chunk.M() );
  CHECK( 4 == chunk.numberRows() );
  CHECK( 4 == chunk.N() );
  CHECK( 4 == chunk.numberColumns() );

  CHECK( 2 == chunk.NSUP() );
  CHECK( 2 == chunk.numberSuperDiagonals() );
  CHECK( 1 == chunk.NSUB() );
  CHECK( 1 == chunk.numberSubDiagonals() );

  CHECK( 12 == chunk.blockLength() );
  CHECK( 12 == chunk.length() );

  CHECK_THAT( 2., WithinRel( chunk.matrixList()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.matrixList()[1] ) );
  CHECK_THAT( 4., WithinRel( chunk.matrixList()[2] ) );

  CHECK_THAT( 1., WithinRel( chunk.matrixList()[3] ) );
  CHECK_THAT( 2., WithinRel( chunk.matrixList()[4] ) );
  CHECK_THAT( 3., WithinRel( chunk.matrixList()[5] ) );
  CHECK_THAT( 4., WithinRel( chunk.matrixList()[6] ) );

  CHECK_THAT( 1., WithinRel( chunk.matrixList()[7] ) );
  CHECK_THAT( 2., WithinRel( chunk.matrixList()[8] ) );
  CHECK_THAT( 3., WithinRel( chunk.matrixList()[9] ) );

  CHECK_THAT( 1., WithinRel( chunk.matrixList()[10] ) );
  CHECK_THAT( 2., WithinRel( chunk.matrixList()[11] ) );

  CHECK( 3 == chunk.rowLength( 1 ) );
  CHECK( 4 == chunk.rowLength( 2 ) );
  CHECK( 3 == chunk.rowLength( 3 ) );
  CHECK( 2 == chunk.rowLength( 4 ) );

  CHECK( 2 == chunk.rowSuperDiagonals( 1 ) );
  CHECK( 2 == chunk.rowSuperDiagonals( 2 ) );
  CHECK( 1 == chunk.rowSuperDiagonals( 3 ) );
  CHECK( 0 == chunk.rowSuperDiagonals( 4 ) );

  CHECK( 0 == chunk.rowSubDiagonals( 1 ) );
  CHECK( 1 == chunk.rowSubDiagonals( 2 ) );
  CHECK( 1 == chunk.rowSubDiagonals( 3 ) );
  CHECK( 1 == chunk.rowSubDiagonals( 4 ) );

  // row 1
  CHECK_THAT( 2., WithinRel( chunk.matrixValue( 1, 1 ) ) );
  CHECK_THAT( 3., WithinRel( chunk.matrixValue( 1, 2 ) ) );
  CHECK_THAT( 4., WithinRel( chunk.matrixValue( 1, 3 ) ) );
  CHECK_THAT( 0., WithinRel( chunk.matrixValue( 1, 4 ) ) );

  CHECK_THAT( 2., WithinRel( chunk.matrixRow( 1 ) [0] ) );
  CHECK_THAT( 3., WithinRel( chunk.matrixRow( 1 ) [1] ) );
  CHECK_THAT( 4., WithinRel( chunk.matrixRow( 1 ) [2] ) );
  CHECK_THAT( 0., WithinRel( chunk.matrixRow( 1 ) [3] ) );

  // row 2
  CHECK_THAT( 1., WithinRel( chunk.matrixValue( 2, 1 ) ) );
  CHECK_THAT( 2., WithinRel( chunk.matrixValue( 2, 2 ) ) );
  CHECK_THAT( 3., WithinRel( chunk.matrixValue( 2, 3 ) ) );
  CHECK_THAT( 4., WithinRel( chunk.matrixValue( 2, 4 ) ) );

  CHECK_THAT( 1., WithinRel( chunk.matrixRow( 2 )[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.matrixRow( 2 )[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.matrixRow( 2 )[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.matrixRow( 2 )[3] ) );

  // row 3
  CHECK_THAT( 0., WithinRel( chunk.matrixValue( 3, 1 ) ) );
  CHECK_THAT( 1., WithinRel( chunk.matrixValue( 3, 2 ) ) );
  CHECK_THAT( 2., WithinRel( chunk.matrixValue( 3, 3 ) ) );
  CHECK_THAT( 3., WithinRel( chunk.matrixValue( 3, 4 ) ) );

  CHECK( 4 == chunk.matrixRow( 3 ).size() );
  CHECK_THAT( 0., WithinRel( chunk.matrixRow( 3 )[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.matrixRow( 3 )[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.matrixRow( 3 )[2] ) );
  CHECK_THAT( 3., WithinRel( chunk.matrixRow( 3 )[3] ) );

  // row 4
  CHECK_THAT( 0., WithinRel( chunk.matrixValue( 4, 1 ) ) );
  CHECK_THAT( 0., WithinRel( chunk.matrixValue( 4, 2 ) ) );
  CHECK_THAT( 1., WithinRel( chunk.matrixValue( 4, 3 ) ) );
  CHECK_THAT( 2., WithinRel( chunk.matrixValue( 4, 4 ) ) );

  CHECK( 4 == chunk.matrixRow( 4 ).size() );
  CHECK_THAT( 0., WithinRel( chunk.matrixRow( 4 )[0] ) );
  CHECK_THAT( 0., WithinRel( chunk.matrixRow( 4 )[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.matrixRow( 4 )[2] ) );
  CHECK_THAT( 2., WithinRel( chunk.matrixRow( 4 )[3] ) );

  auto mat = chunk.matrix();
  for (unsigned int row = 1; row <= 4; ++row ){
    for (unsigned int col = 1; col <= 4; ++col ) {
      CHECK_THAT( ans[row-1][col-1], WithinRel( mat[row-1][col-1] ) );
    }
  }
}
