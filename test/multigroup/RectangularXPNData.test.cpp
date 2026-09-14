// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/RectangularXPNData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using RectangularXPNData = multigroup::RectangularXPNData;

std::vector< double > chunk();
void verifyChunk( const RectangularXPNData&, std::vector< double >&, std::vector< std::vector< int > >& );
RectangularXPNData makeDummyBlock();

SCENARIO( "RectangularXPNData" ) {

  GIVEN( "valid data for a RectangularXPNData instance" ) {

    std::vector< double > xss = chunk();

    std::vector < std::vector < int > > values = {
       {  1,  5,  9, 13, 17 },
       { 21, 25, 29, 33, 37 },
       { 41, 45, 49, 53, 57 }, 
       { 61, 65, 69, 73, 77 }, 
       { 81, 85, 89, -1, -1 },
       { -1, -1, -1, -1, -1 }
      };

    WHEN( "the data is given explicitly" ) {

        RectangularXPNData chunk( std::move( values ) );


      THEN( "an RectangularXPNData can be constructed and "
            "members can be tested" ) {
            
          verifyChunk( chunk, xss, values );

      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      RectangularXPNData chunk( xss.begin(), xss.end(), 6, 5 );

      THEN( "a RectangularXPNData can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss, values );
      } // THEN
    } // WHEN


  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

   return { 1,  5,  9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61, 65, 69, 73, 77, 81, 85, 89, -1, -1, -1, -1, -1, -1, -1 };
}


void verifyChunk( const RectangularXPNData& chunk, std::vector< double >& xss, std::vector< std::vector< int > >& ans ) {

// XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

// interface

  CHECK( 6 == chunk.NGRP() );
  CHECK( 6 == chunk.numberIncidentEnergyGroups() );

  CHECK( 5 == chunk.NERG() );
  CHECK( 5 == chunk.numberOutgoingEnergyGroups() );

  CHECK( 30 == chunk.blockLength() );
  CHECK( 30 == chunk.length() );

  for ( int i = 0; i < 6; ++i) {

    CHECK( 5 == chunk.incidentRow( i+1 ).size());
    for ( int j = 0; j < 5; ++j ) {

      CHECK( 6 == chunk.outgoingColumn( j+1 ).size());

      CHECK( ans[i][j] == chunk.XPNMatrixList()[ 5*i + j] );
      CHECK( ans[i][j] == chunk.LPND( i+1, j+1) );
      CHECK( ans[i][j] == chunk.locator( i+1, j+1) );
      CHECK( ans[i][j] == chunk.incidentRow( i+1 ) [j] );
      CHECK( ans[i][j] == chunk.outgoingColumn( j+1 ) [i] );
    }
  }

  auto mat = chunk.XPNMatrix();
  for (unsigned int row = 1; row <= 4; ++row ){
    for (unsigned int col = 1; col <= 4; ++col ) {
      CHECK_THAT( ans[row-1][col-1], WithinRel( mat[row-1][col-1] ) );
    }
  }
}

