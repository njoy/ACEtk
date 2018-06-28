#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;
using namespace njoy::ACEtk;

SCENARIO( "Law4" ){
  GIVEN( "valid input parameters" ){
    std::vector< int > validINT{  
      1,  2,  3,  4,  5,  6, 11, 12, 13, 14, 15, 11, 21, 22, 23, 24, 25 };

    WHEN( "inputs are simple arrays" ){
      std::vector< double > x{ 1.0, 2.0, 3.0 };
      std::vector< double > y{ 0.1, 0.2, 0.3 };

      for( int INT : validINT ){
        Region< std::vector< double >, std::vector< double > > regSimple( 
            INT, Table::slice( x ), Table::slice( y ) );

        THEN( "the outputs can be veirified (INT=" 
              + std::to_string( INT ) + ")" ){
          REQUIRE( INT == regSimple.interpolationScheme() );
          REQUIRE( ranges::equal( x, regSimple.x() ) );
          REQUIRE( ranges::equal( y, regSimple.y() ) );
        }
      }
    }
    WHEN( "inputs are more complicated" ){
      std::vector< double > x{ 1.0, 2.0, 3.0 };
      std::vector< std::vector< double > > y{
        { 0.1, 0.2, 0.3 },
        { 1.1, 1.2, 1.3 },
        { 2.1, 2.2, 2.3 }
      };
      for( int INT : validINT ){
        Region< std::vector< double >, std::vector< std::vector< double > > >
            regSimple( INT, std::move( x ), std::move( y ) );

        THEN( "the outputs can be veirified (INT=" 
              + std::to_string( INT ) + ")" ){
          REQUIRE( INT == regSimple.interpolationScheme() );
          REQUIRE( ranges::equal( x, regSimple.x() ) );
          REQUIRE( ranges::equal( y, regSimple.y() ) );
        }
      }
    }
  } // GIVEN valid
  GIVEN( "invalid input parameters" ){
    std::vector< double > x{ 1.0, 2.0, 3.0 };
    std::vector< double > y{ 0.1, 0.2, 0.3 };

    using region = Region< std::vector< double >, std::vector< double > >;
    WHEN( "invalid interpolation parameters" ){
      std::vector< int > invalidINT{ 0, 7, 8, 9, 10, 16, 17, 18, 19, 20, 27 };

      for( int INT : invalidINT ){
        THEN( "an exception is thrown INT: (" + std::to_string( INT ) +")" ){
          REQUIRE_THROWS( region( INT, Table::slice( x ), Table::slice( y ) ) );
        }
      }
    }
    WHEN( "x and y are not the same size" ){
      y = { 0.1, 0.2 };
      THEN( "an exception is thrown " ){
        REQUIRE_THROWS( region( 2, std::move( x ), std::move( y ) ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO
