#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/XsdirEntry.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;

std::string chunk();
std::string chunkWithSplit();
std::string chunkWith7entries();
std::string chunkWith10entries();
void verifyChunk( const XsdirEntry& );
void verifyChunkWithSplit( const XsdirEntry& );
void verifyChunkWith7entries( const XsdirEntry& );
void verifyChunkWith10entries( const XsdirEntry& );

SCENARIO( "XsdirEntry" ) {

  GIVEN( "valid data for an XsdirEntry instance" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::string zaid = "92235.00c";
      double awr = 235.;
      std::string filename = "file";
      unsigned int address = 5;
      unsigned int tablelength = 1000;
      double temperature = 2.53e-8;
      bool ptable = true;

      XsdirEntry chunk( std::move( zaid ), awr, std::move( filename ),
                        address, tablelength, temperature, ptable );

      THEN( "an XsdirEntry can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::istringstream in ( string );
      XsdirEntry chunk( in );

      THEN( "an XsdirEntry can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for an XsdirEntry instance printed on multiple lines" ) {

    std::string string = chunkWithSplit();

    WHEN( "the data is given explicitly" ) {

      std::string zaid = "92235.00c";
      double awr = 235.;
      std::string filename = "filenamethatiswaaaaaaaaaaaaaaaaaaaaaaaaaytoolong";
      unsigned int address = 5;
      unsigned int tablelength = 1000;
      double temperature = 2.53e-8;
      bool ptable = true;
      std::string access = "accessnamethatisevenwaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaylonger";

      XsdirEntry chunk( std::move( zaid ), awr, std::move( filename ),
                        address, tablelength, temperature, ptable, access );

      THEN( "an XsdirEntry can be constructed and members can be tested" ) {

        verifyChunkWithSplit( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::istringstream in ( string );
      XsdirEntry chunk( in );

      THEN( "an XsdirEntry can be constructed and members can be tested" ) {

        verifyChunkWithSplit( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for an XsdirEntry instance with 7 entries" ) {

    std::string string = chunkWith7entries();

    WHEN( "the data is given explicitly" ) {

      std::string zaid = "92235.00c";
      double awr = 235.;
      std::string filename = "file";
      unsigned int address = 5;
      unsigned int tablelength = 1000;

      XsdirEntry chunk( std::move( zaid ), awr, std::move( filename ),
                        address, tablelength );

      THEN( "an XsdirEntry can be constructed and members can be tested" ) {

        verifyChunkWith7entries( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::istringstream in ( string );
      XsdirEntry chunk( in );

      THEN( "an XsdirEntry can be constructed and members can be tested" ) {

        verifyChunkWith7entries( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for an XsdirEntry instance with 10 entries" ) {

    std::string string = chunkWith10entries();

    WHEN( "the data is given explicitly" ) {

      std::string zaid = "92235.00c";
      double awr = 235.;
      std::string filename = "file";
      unsigned int address = 5;
      unsigned int tablelength = 1000;
      std::optional< double > temperature = 2.53e-8;

      XsdirEntry chunk( std::move( zaid ), awr, std::move( filename ),
                        address, tablelength, temperature );

      THEN( "an XsdirEntry can be constructed and members can be tested" ) {

        verifyChunkWith10entries( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      std::istringstream in ( string );
      XsdirEntry chunk( in );

      THEN( "an XsdirEntry can be constructed and members can be tested" ) {

        verifyChunkWith10entries( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    "    92235.00c   235.000000 file 0 1 5 1000 0 0 2.530000e-08 ptable\n";
}

void verifyChunk( const XsdirEntry& chunk ) {

  CHECK( "92235.00c" == chunk.ZAID() );
  CHECK( 235. == Approx( chunk.AWR() ) );
  CHECK( 235. == Approx( chunk.atomicWeightRatio() ) );
  CHECK( "file" == chunk.fileName() );
  CHECK( std::nullopt == chunk.accessRoute() );
  CHECK( 1 == chunk.fileType() );
  CHECK( 5 == chunk.address() );
  CHECK( 1000 == chunk.tableLength() );
  CHECK( std::nullopt == chunk.recordLength() );
  CHECK( std::nullopt == chunk.entriesPerRecord() );
  CHECK( std::nullopt != chunk.temperature() );
  CHECK( 2.53e-8 == Approx( chunk.temperature().value() ) );
  CHECK( true == chunk.ptable() );
}

std::string chunkWithSplit() {

  return
    "    92235.00c   235.000000 filenamethatiswaaaaaaaaaaaaaaaaaaaaaaaaaytoolong +\n"
    "     accessnamethatisevenwaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaylonger 1 5 1000 0 0 2.530000e-08 +\n"
    "     ptable\n";
}

void verifyChunkWithSplit( const XsdirEntry& chunk ) {

  CHECK( "92235.00c" == chunk.ZAID() );
  CHECK( 235. == Approx( chunk.AWR() ) );
  CHECK( 235. == Approx( chunk.atomicWeightRatio() ) );
  CHECK( "filenamethatiswaaaaaaaaaaaaaaaaaaaaaaaaaytoolong" == chunk.fileName() );
  CHECK( "accessnamethatisevenwaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaylonger"
         == chunk.accessRoute().value() );
  CHECK( 1 == chunk.fileType() );
  CHECK( 5 == chunk.address() );
  CHECK( 1000 == chunk.tableLength() );
  CHECK( std::nullopt == chunk.recordLength() );
  CHECK( std::nullopt == chunk.entriesPerRecord() );
  CHECK( std::nullopt != chunk.temperature() );
  CHECK( 2.53e-8 == Approx( chunk.temperature().value() ) );
  CHECK( true == chunk.ptable() );
}

std::string chunkWith7entries() {

  return
    "    92235.00c   235.000000 file 0 1 5 1000\n";
}

void verifyChunkWith7entries( const XsdirEntry& chunk ) {

  CHECK( "92235.00c" == chunk.ZAID() );
  CHECK( 235. == Approx( chunk.AWR() ) );
  CHECK( 235. == Approx( chunk.atomicWeightRatio() ) );
  CHECK( "file" == chunk.fileName() );
  CHECK( std::nullopt == chunk.accessRoute() );
  CHECK( 1 == chunk.fileType() );
  CHECK( 5 == chunk.address() );
  CHECK( 1000 == chunk.tableLength() );
  CHECK( std::nullopt == chunk.recordLength() );
  CHECK( std::nullopt == chunk.entriesPerRecord() );
  CHECK( std::nullopt == chunk.temperature() );
  CHECK( false == chunk.ptable() );
}

std::string chunkWith10entries() {

  return
    "    92235.00c   235.000000 file 0 1 5 1000 0 0 2.530000e-08\n";
}

void verifyChunkWith10entries( const XsdirEntry& chunk ) {

  CHECK( "92235.00c" == chunk.ZAID() );
  CHECK( 235. == Approx( chunk.AWR() ) );
  CHECK( 235. == Approx( chunk.atomicWeightRatio() ) );
  CHECK( "file" == chunk.fileName() );
  CHECK( std::nullopt == chunk.accessRoute() );
  CHECK( 1 == chunk.fileType() );
  CHECK( 5 == chunk.address() );
  CHECK( 1000 == chunk.tableLength() );
  CHECK( std::nullopt == chunk.recordLength() );
  CHECK( std::nullopt == chunk.entriesPerRecord() );
  CHECK( std::nullopt != chunk.temperature() );
  CHECK( 2.53e-8 == Approx( chunk.temperature().value() ) );
  CHECK( false == chunk.ptable() );
}
