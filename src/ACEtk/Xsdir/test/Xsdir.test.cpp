#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/Xsdir.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;

std::string chunk();
void verifyChunk( const Xsdir& );

SCENARIO( "Xsdir" ) {

  GIVEN( "valid data for an Xsdir instance" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {


      std::vector< XsdirEntry > entries = {

        XsdirEntry( "92234.00c", 234., "file", 5, 1000, 2.53e-8, false ),
        XsdirEntry( "92235.00c", 235., "file2", 3, 2000, 2.53e-8, true ),
        XsdirEntry( "92000.00p", 233., "file3", 4, 3000 )
      };

      Xsdir chunk( std::move( entries ) );

      THEN( "an Xsdir can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        oss << chunk;

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::istringstream in( string );
      Xsdir chunk;
      in >> chunk;

      THEN( "an Xsdir can be constructed and members can be tested" ) {

        verifyChunk( chunk );

        CHECK( true == in.eof() );
        CHECK( true == in.fail() );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        oss << chunk;

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    "directory\n"
    " 92234.00c   234.000000 file 0 1 5 1000 0 0 2.530000e-08\n"
    " 92235.00c   235.000000 file2 0 1 3 2000 0 0 2.530000e-08 ptable\n"
    " 92000.00p   233.000000 file3 0 1 4 3000\n";
}

void verifyChunk( const Xsdir& chunk ) {

  CHECK( std::nullopt == chunk.dataPath() );

  CHECK( 3 == chunk.entries().size() );
  CHECK( "92234.00c" == chunk.entries()[0].ZAID() );
  CHECK( "92235.00c" == chunk.entries()[1].ZAID() );
  CHECK( "92000.00p" == chunk.entries()[2].ZAID() );

  auto entry = chunk.entry( "92234.00c" );
  CHECK( "92234.00c" == entry.ZAID() );

  entry = chunk.entry( "92235.00c" );
  CHECK( "92235.00c" == entry.ZAID() );

  entry = chunk.entry( "92000.00p" );
  CHECK( "92000.00p" == entry.ZAID() );
}
