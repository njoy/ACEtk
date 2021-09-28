#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/Table.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using Header = Table::Header;

std::string chunk();
std::string chunkWith200Header();
std::string chunkWith201Header();
void verifyChunk( const Header& );

SCENARIO( "Header" ) {

  GIVEN( "valid data for a Header instance" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::string zaid = "92238.80c";
      double awr = 236.0058;
      double temperature = 2.5301E-08;
      std::string date = "12/13/12";
      std::string title = "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)";
      std::string material = "mat9237";

      Header chunk( zaid, awr, temperature, date, title, material );

      THEN( "a Header can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with the normal header" ) {

      State< std::string::iterator > state{ 1, string.begin(), string.end() };
      Header chunk( state );

      THEN( "a Header can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed with the normal header" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with the 2.0.0 header" ) {

      std::string header = chunkWith200Header();
      State< std::string::iterator > state{ 1, header.begin(), header.end() };
      Header chunk( state );

      THEN( "a Header can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed with the normal header" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with the 2.0.1 header" ) {

      std::string header = chunkWith201Header();
      State< std::string::iterator > state{ 1, header.begin(), header.end() };
      Header chunk( state );

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
    " 92238.80c  236.005800  2.5301E-08   12/13/12\n"
    "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237\n";
}

void verifyChunk( const Header& chunk ) {

  CHECK( "92238.80c" == chunk.ZAID() );
  CHECK( 236.0058 == Approx( chunk.AWR() ) );
  CHECK( 236.0058 == Approx( chunk.atomicWeightRatio() ) );
  CHECK( 2.5301E-08 == Approx( chunk.TEMP() ) );
  CHECK( 2.5301E-08 == Approx( chunk.temperature() ) );
  CHECK( "12/13/12" == chunk.date() );
  CHECK( "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)"
         == chunk.title() );
  CHECK( "mat9237" == chunk.material() );
}

std::string chunkWith200Header() {

  return
    "2.0.0     92238.710nc              ENDFB-VII.1\n"
    "236.005800 2.5301E-08 12/13/12     3\n"
    "some additional comments on this file\n"
    " 92238.80c  236.005800  2.5301E-08   12/13/12\n"
    "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237\n";
}

std::string chunkWith201Header() {

  return
    "2.0.1                   92238.800nc         ENDF/B-VIII.0\n"
    "  236.005800   2.5301e-08 2018-05-01    2\n"
    " 92238.80c  236.005800  2.5301E-08   12/13/12\n"
    "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237\n";
}
