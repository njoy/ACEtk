#define CATCH_CONFIG_MAIN

#include "catch.hpp"
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
  CHECK( 236.0058 == Approx( chunk.AWR() ) );
  CHECK( 236.0058 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 2.5301E-08 == Approx( chunk.TEMP() ) );
  CHECK( 2.5301E-08 == Approx( chunk.temperature() ) );
  CHECK( "2018-05-01" == chunk.date() );
//  CHECK( "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)"
//         == chunk.title() );
//  CHECK( "mat9237" == chunk.material() );
}
