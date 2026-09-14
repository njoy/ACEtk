// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/base/RectangularMatrixData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using RectangularMatrixData = base::RectangularMatrixData;

std::vector< double > chunk();

void verifyChunk( const RectangularMatrixData&, std::vector< double >&);
void verifyIntegerChunk( const RectangularMatrixData&, std::vector< double >&);

RectangularMatrixData makeDummyBlock();

SCENARIO( "RectangularMatrixData" ) {

  GIVEN( "valid data for a RectangularMatrixData instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

        std::vector < std::vector < double > > values = {
            {  2.,  3.,  4.,  5. },
            {  1.,  2.,  3.,  4. },
            { 10., 11., 12., 13. },
        };

        RectangularMatrixData chunk( "Band", std::move( values ) );


      THEN( "an RectangularMatrixData can be constructed and "
            "members can be tested" ) {
            
          verifyChunk( chunk, xss );

      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      RectangularMatrixData chunk( "Band", xss.begin(), xss.end(), 3, 4);

      THEN( "a RectangularMatrixData can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN


  } // GIVEN
  GIVEN( "valid integer data for a RectangularMatrixData instance" ) {

    std::vector< double > xssInteger = chunk();

    WHEN( "the data is given explicitly" ) {

        std::vector < std::vector < unsigned int > > values = {
            {  2,  3,  4,  5 },
            {  1,  2,  3,  4 },
            { 10, 11, 12, 13 },
        };

        RectangularMatrixData chunk( "Rectangular", std::move( values ) );


      THEN( "an RectangularMatrixData can be constructed and "
            "members can be tested" ) {
            
          verifyIntegerChunk( chunk, xssInteger );

      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      RectangularMatrixData chunk( "Rectangular", xssInteger.begin(), xssInteger.end(), 3, 4);

      THEN( "a RectangularMatrixData can be constructed and members can be tested" ) {

        verifyIntegerChunk( chunk, xssInteger );
      } // THEN
    } // WHEN


  } // GIVEN
} // SCENARIO



std::vector< double > chunk() {

   return { 2., 3., 4., 5., 1., 2., 3., 4., 10., 11., 12., 13. };
}



void verifyChunk( const RectangularMatrixData& chunk, std::vector< double >& xss ) {

    std::vector < std::vector < double > > ans = {
            {  2.,  3.,  4.,  5. },
            {  1.,  2.,  3.,  4. },
            { 10., 11., 12., 13. },
    };

// XSS

  auto xss_chunk = chunk.XSS();
  auto mat = chunk.dmatrix();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
    CHECK_THAT( xss[i], WithinRel( mat[i] ) );
  }

// interface

  CHECK( 3 == chunk.M() );
  CHECK( 3 == chunk.numberRows() );
  CHECK( 4 == chunk.N() );
  CHECK( 4 == chunk.numberColumns() );

  CHECK( 12 == chunk.numberValues() );
  CHECK( 12 == chunk.length() );


  // row 1
  CHECK_THAT( 2., WithinRel( chunk.dvalue( 1, 1 ) ) );
  CHECK_THAT( 3., WithinRel( chunk.dvalue( 1, 2 ) ) );
  CHECK_THAT( 4., WithinRel( chunk.dvalue( 1, 3 ) ) );
  CHECK_THAT( 5., WithinRel( chunk.dvalue( 1, 4 ) ) );

  CHECK_THAT( 2., WithinRel( chunk.drow( 1 ) [0] ) );
  CHECK_THAT( 3., WithinRel( chunk.drow( 1 ) [1] ) );
  CHECK_THAT( 4., WithinRel( chunk.drow( 1 ) [2] ) );
  CHECK_THAT( 5., WithinRel( chunk.drow( 1 ) [3] ) );

  // row 2
  CHECK_THAT( 1., WithinRel( chunk.dvalue( 2, 1 ) ) );
  CHECK_THAT( 2., WithinRel( chunk.dvalue( 2, 2 ) ) );
  CHECK_THAT( 3., WithinRel( chunk.dvalue( 2, 3 ) ) );
  CHECK_THAT( 4., WithinRel( chunk.dvalue( 2, 4 ) ) );

  CHECK_THAT( 1., WithinRel( chunk.drow( 2 )[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.drow( 2 )[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.drow( 2 )[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.drow( 2 )[3] ) );

  // row 3
  CHECK( 4 == chunk.drow( 3 ).size() );
  CHECK_THAT( 10., WithinRel( chunk.drow( 3 )[0] ) );
  CHECK_THAT( 11., WithinRel( chunk.drow( 3 )[1] ) );
  CHECK_THAT( 12., WithinRel( chunk.drow( 3 )[2] ) );
  CHECK_THAT( 13., WithinRel( chunk.drow( 3 )[3] ) );


  CHECK_THAT( 2., WithinRel( chunk.dcolumn( 1 )[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.dcolumn( 1 )[1] ) );
  CHECK_THAT( 10., WithinRel( chunk.dcolumn( 1 )[2] ) );

  CHECK_THAT( 3., WithinRel( chunk.dcolumn( 2 )[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.dcolumn( 2 )[1] ) );
  CHECK_THAT( 11., WithinRel( chunk.dcolumn( 2 )[2] ) );

  CHECK_THAT( 4., WithinRel( chunk.dcolumn( 3 )[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.dcolumn( 3 )[1] ) );
  CHECK_THAT( 12., WithinRel( chunk.dcolumn( 3 )[2] ) );

  CHECK_THAT( 5., WithinRel( chunk.dcolumn( 4 )[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.dcolumn( 4 )[1] ) );
  CHECK_THAT( 13., WithinRel( chunk.dcolumn( 4 )[2] ) );

  auto matrix = chunk.matrix();
  for (unsigned int row = 1; row <= chunk.M(); ++row ){
    for (unsigned int col = 1; col <= chunk.N(); ++col ) {
      CHECK_THAT( ans[row-1][col-1], WithinRel( matrix[row-1][col-1] ) );
    }
  }
}

void verifyIntegerChunk( const RectangularMatrixData& chunk, std::vector< double >& xss ) {

    std::vector < std::vector < unsigned int > > ans = {
            {  2,  3,  4,  5 },
            {  1,  2,  3,  4 },
            { 10, 11, 12, 13 },
    };

// XSS

  auto xss_chunk = chunk.XSS();
  auto mat = chunk.dmatrix();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK( xss[i] == xss_chunk[i] );
    CHECK( xss[i] == mat[i] );
  }

// interface

  CHECK( 3 == chunk.M() );
  CHECK( 3 == chunk.numberRows() );
  CHECK( 4 == chunk.N() );
  CHECK( 4 == chunk.numberColumns() );

  CHECK( 12 == chunk.numberValues() );
  CHECK( 12 == chunk.length() );


  // row 1
  CHECK( 2 == chunk.ivalue( 1, 1 ) );
  CHECK( 3 == chunk.ivalue( 1, 2 ) );
  CHECK( 4 == chunk.ivalue( 1, 3 ) );
  CHECK( 5 == chunk.ivalue( 1, 4 ) );

  CHECK( 2 == chunk.irow( 1 ) [0] );
  CHECK( 3 == chunk.irow( 1 ) [1] );
  CHECK( 4 == chunk.irow( 1 ) [2] );
  CHECK( 5 == chunk.irow( 1 ) [3] );

  // row 2
  CHECK( 1 == chunk.ivalue( 2, 1 ) );
  CHECK( 2 == chunk.ivalue( 2, 2 ) );
  CHECK( 3 == chunk.ivalue( 2, 3 ) );
  CHECK( 4 == chunk.ivalue( 2, 4 ) );

  CHECK( 1 == chunk.irow( 2 )[0] );
  CHECK( 2 == chunk.irow( 2 )[1] );
  CHECK( 3 == chunk.irow( 2 )[2] );
  CHECK( 4 == chunk.irow( 2 )[3] );

  // row 3
  CHECK( 4 == chunk.irow( 3 ).size() );
  CHECK( 10 == chunk.irow( 3 )[0] ); 
  CHECK( 11 == chunk.irow( 3 )[1] ); 
  CHECK( 12 == chunk.irow( 3 )[2] ); 
  CHECK( 13 == chunk.irow( 3 )[3] ); 


  CHECK(  2 == chunk.icolumn( 1 )[0] );
  CHECK(  1 == chunk.icolumn( 1 )[1] );
  CHECK( 10 == chunk.icolumn( 1 )[2] );

  CHECK(  3 == chunk.icolumn( 2 )[0] );
  CHECK(  2 == chunk.icolumn( 2 )[1] );
  CHECK( 11 == chunk.icolumn( 2 )[2] );

  CHECK(  4 == chunk.icolumn( 3 )[0] );
  CHECK(  3 == chunk.icolumn( 3 )[1] );
  CHECK( 12 == chunk.icolumn( 3 )[2] );

  CHECK(  5 == chunk.icolumn( 4 )[0] );
  CHECK(  4 == chunk.icolumn( 4 )[1] );
  CHECK( 13 == chunk.icolumn( 4 )[2] );

  auto matrix = chunk.matrix();
  for (unsigned int row = 1; row <= chunk.M(); ++row ){
    for (unsigned int col = 1; col <= chunk.N(); ++col ) {
      CHECK( ans[row-1][col-1] == matrix[row-1][col-1] );
    }
  }

}


