// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/base/SquareBandMatrixData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using SquareBandMatrixData = base::SquareBandMatrixData;

std::vector< double > chunk();
std::vector< double > fullChunk();
std::vector< double > diagonalChunk();
void verifyChunk( const SquareBandMatrixData&, std::vector< double >&);
void verifyFullChunk( const SquareBandMatrixData&, std::vector< double >&);
void verifyDiagonalChunk( const SquareBandMatrixData&, std::vector< double >&);
SquareBandMatrixData makeDummyBlock();

SCENARIO( "SquareBandMatrixData" ) {

  GIVEN( "valid data for a SquareBandMatrixData instance" ) {

    std::vector< double > xss = chunk();
    std::vector< double > fullXSS = fullChunk();
    std::vector< double > diagonalXSS = diagonalChunk();

    WHEN( "the data is given explicitly" ) {

        std::vector < std::vector < double > > values = {
            { 2., 3., 4., 0. },
            { 1., 2., 3., 4. },
            { 0., 1., 2., 3. },
            { 0., 0., 1., 2. }
        };

        SquareBandMatrixData chunk( "Band", std::move( values ), 2, 1 );


      THEN( "an SquareBandMatrixData can be constructed and "
            "members can be tested" ) {
            
          verifyChunk( chunk, xss );

      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      SquareBandMatrixData chunk( "Band", xss.begin(), xss.end(), 4, 2, 1 );

      THEN( "a SquareBandMatrixData can be constructed and members can be tested" ) {

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

        SquareBandMatrixData chunk( "Band", std::move( badValues ), 2, 1 );


      THEN( "those values are thrown away" ) {
            
          verifyChunk( chunk, xss );

      } // THEN
    } // WHEN


    WHEN( "given a full matrix" ) {

        std::vector < std::vector < double > > fullMatrix = {
            { 2., 3., 4., 5. },
            { 1., 2., 3., 4. },
            { 8., 1., 2., 3. },
            { 9., 6., 1., 2. }
        };

        SquareBandMatrixData fullChunk( "Band", std::move( fullMatrix ), 3, 3 );


      THEN( "the SquareBandMatrixData is constructed correctly" ) {
            
          verifyFullChunk( fullChunk, fullXSS );

      } // THEN
    } // WHEN

    WHEN( "given a diagonal matrix" ) {

        std::vector < std::vector < double > > diagonalMatrix = {
            { 1., 0., 0., 0. },
            { 0., 2., 0., 0. },
            { 0., 0., 3., 0. },
            { 0., 0., 0., 4. }
        };

        SquareBandMatrixData diagonalChunk( "Band", std::move( diagonalMatrix ), 0, 0 );


      THEN( "the SquareBandMatrixData is constructed correctly" ) {
            
          verifyDiagonalChunk( diagonalChunk, diagonalXSS );

      } // THEN
    } // WHEN

  //  @TODO Figure out how to test exceptions thrown by the constructor itselfs

  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

   return { 2., 3., 4., 1., 2., 3., 4., 1., 2., 3., 1., 2. };
}


std::vector< double > fullChunk() {

   return { 2., 3., 4., 5., 1., 2., 3., 4., 8., 1., 2., 3., 9., 6., 1., 2. };
}


std::vector< double > diagonalChunk() {

   return { 1., 2., 3., 4. };
}


void verifyChunk( const SquareBandMatrixData& chunk, std::vector< double >& xss ) {

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



void verifyFullChunk( const SquareBandMatrixData& chunk, std::vector< double >& xss ) {

    std::vector < std::vector < double > > ans = {
            { 2., 3., 4., 5. },
            { 1., 2., 3., 4. },
            { 8., 1., 2., 3. },
            { 9., 6., 1., 2. }
    };


  CHECK( 4 == chunk.size() );
  CHECK( 4 == chunk.M() );
  CHECK( 4 == chunk.numberRows() );
  CHECK( 4 == chunk.N() );
  CHECK( 4 == chunk.numberColumns() );

  CHECK( 3 == chunk.NSUP() );
  CHECK( 3 == chunk.numberSuperDiagonals() );
  CHECK( 3 == chunk.NSUB() );
  CHECK( 3 == chunk.numberSubDiagonals() );

  CHECK( 16 == chunk.blockLength() );
  CHECK( 16 == chunk.length() );

// XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  auto mat = chunk.matrix();
  for (unsigned int row = 1; row <= 4; ++row ){
    for (unsigned int col = 1; col <= 4; ++col ) {
      CHECK_THAT( ans[row-1][col-1], WithinRel( mat[row-1][col-1] ) );
    }
  }
}


void verifyDiagonalChunk( const SquareBandMatrixData& chunk, std::vector< double >& xss ) {

    std::vector < std::vector < double > > ans = {
            { 1., 0., 0., 0. },
            { 0., 2., 0., 0. },
            { 0., 0., 3., 0. },
            { 0., 0., 0., 4. }
    };


  CHECK( 4 == chunk.size() );
  CHECK( 4 == chunk.M() );
  CHECK( 4 == chunk.numberRows() );
  CHECK( 4 == chunk.N() );
  CHECK( 4 == chunk.numberColumns() );

  CHECK( 0 == chunk.NSUP() );
  CHECK( 0 == chunk.numberSuperDiagonals() );
  CHECK( 0 == chunk.NSUB() );
  CHECK( 0 == chunk.numberSubDiagonals() );

  CHECK( 4 == chunk.blockLength() );
  CHECK( 4 == chunk.length() );

// XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  auto mat = chunk.matrix();
  for (unsigned int row = 1; row <= 4; ++row ){
    for (unsigned int col = 1; col <= 4; ++col ) {
      CHECK_THAT( ans[row-1][col-1], WithinRel( mat[row-1][col-1] ) );
    }
  }
}