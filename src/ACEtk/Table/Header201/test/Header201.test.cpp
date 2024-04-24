// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/Table.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using Header201 = Table::Header201;

std::string chunk();
void verifyChunk( const Header201& );

SCENARIO( "Header201" ) {

  GIVEN( "valid data for a Header201 instance" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::string szaid = "92238.800nc";
      std::string source = "ENDF/B-VIII.0";
      double awr = 236.0058;
      double temperature = 2.5301E-08;
      std::string date = "2018-05-01";

      std::vector< std::string > comments = {

        " 92238.80c  236.005800  2.5301E-08   12/13/12",
        "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237"
      };

      Header201 chunk( szaid, source, awr, temperature, date, comments );

      THEN( "a Header can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with the header" ) {

      State< std::string::iterator > state{ 1, string.begin(), string.end() };
      Header201 chunk( state );

      THEN( "a Header can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed with the normal header" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
  "2.0.1                   92238.800nc            ENDF/B-VIII.0\n"
  "  236.005800   2.5301E-08 2018-05-01          2\n"
  " 92238.80c  236.005800  2.5301E-08   12/13/12\n"
  "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237\n";
}

void verifyChunk( const Header201& chunk ) {

  CHECK( "2.0.1" == chunk.VERS() );
  CHECK( "2.0.1" == chunk.version() );
  CHECK( "92238.800nc" == chunk.ZAID() );
  CHECK_THAT( 236.0058, WithinRel( chunk.AWR() ) );
  CHECK_THAT( 236.0058, WithinRel( chunk.atomicWeightRatio() ) );
  CHECK_THAT( 2.5301E-08, WithinRel( chunk.TEMP() ) );
  CHECK_THAT( 2.5301E-08, WithinRel( chunk.temperature() ) );
  CHECK( "2018-05-01" == chunk.date() );
  CHECK( " 92238.80c  236.005800  2.5301E-08   12/13/12" == chunk.comments()[0] );
  CHECK( "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237"
         == chunk.comments()[1] );
}
