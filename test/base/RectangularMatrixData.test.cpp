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

      RectangularMatrixData chunk( "Band", xss.begin(), xss.end(), 3, 4 );

      THEN( "a RectangularMatrixData can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
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

