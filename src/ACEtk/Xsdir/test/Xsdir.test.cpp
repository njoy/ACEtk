// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/Xsdir.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;

std::string chunk();
std::string chunkWithCommentLines();
std::string chunkWithUpperCaseAndTrailingWhitespace();
void verifyChunk( const Xsdir& );
std::string chunkWithoutDatapath();
void verifyChunkWithoutDatapath( const Xsdir& );

SCENARIO( "Xsdir" ) {

  GIVEN( "valid data for an Xsdir instance" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::string datapath = "/some/path/to/Data";

      std::map< unsigned int, double > ratios = {

        {       1,   1.00000000 },
        {    1000,   0.99931697 },
        {    1001,   0.99916733 },
        {    1002,   1.99679968 },
        {    1003,   2.99013997 },
        {    1004,   3.99320563 },
        {   92000, 235.98412800 },
        {   92235, 233.02478975 },
        { 1092235, 233.02478975 }
      };

      std::vector< XsdirEntry > entries = {

        XsdirEntry( "92234.00c", 234., "file", 5, 1000, 2.53e-8, false ),
        XsdirEntry( "92235.00c", 235., "file2", 3, 2000, 2.53e-8, true ),
        XsdirEntry( "92000.00p", 233., "file3", 4, 3000 )
      };

      Xsdir chunk( std::move( ratios ), std::move( entries ),
                   std::move( datapath ) );

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

    WHEN( "the data is read from a string/stream with some uppercase and "
          "trailing whitespace" ) {

      std::istringstream in( chunkWithUpperCaseAndTrailingWhitespace() );
      Xsdir chunk;
      in >> chunk;

      THEN( "an Xsdir can be constructed and members can be tested" ) {

        verifyChunk( chunk );

        CHECK( true == in.eof() );
        CHECK( true == in.fail() );
      } // THEN

      THEN( "it can be printed but it will not have the upper case text or "
            "the trailing whitespace" ) {

        std::ostringstream oss;
        oss << chunk;

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with some comment lines" ) {

      std::istringstream in( chunkWithCommentLines() );
      Xsdir chunk;
      in >> chunk;

      THEN( "an Xsdir can be constructed and members can be tested" ) {

        verifyChunk( chunk );

        CHECK( true == in.eof() );
        CHECK( true == in.fail() );
      } // THEN

      THEN( "it can be printed but it will not have the upper case text or "
            "the trailing whitespace" ) {

        std::ostringstream oss;
        oss << chunk;

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for an Xsdir instance without a datapath" ) {

    std::string string = chunkWithoutDatapath();

    WHEN( "the data is given explicitly" ) {

      std::map< unsigned int, double > ratios = {

        {       1,   1.00000000 },
        {    1000,   0.99931697 },
        {    1001,   0.99916733 },
        {    1002,   1.99679968 },
        {    1003,   2.99013997 },
        {    1004,   3.99320563 },
        {   92000, 235.98412800 },
        {   92235, 233.02478975 },
        { 1092235, 233.02478975 }
      };

      std::vector< XsdirEntry > entries = {

        XsdirEntry( "92234.00c", 234., "file", 5, 1000, 2.53e-8, false ),
        XsdirEntry( "92235.00c", 235., "file2", 3, 2000, 2.53e-8, true ),
        XsdirEntry( "92000.00p", 233., "file3", 4, 3000 )
      };

      Xsdir chunk( std::move( ratios ), std::move( entries ) );

      THEN( "an Xsdir can be constructed and members can be tested" ) {

        verifyChunkWithoutDatapath( chunk );
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

        verifyChunkWithoutDatapath( chunk );

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
    "datapath=/some/path/to/Data\n"
    "atomic weight ratios\n"
    "       1   1.00000000\n"
    "    1000   0.99931697    1001   0.99916733    1002   1.99679968    1003   2.99013997\n"
    "                         1004   3.99320563\n"
    "   92000 235.98412800   92235 233.02478975 1092235 233.02478975\n"
    "\n"
    "directory\n"
    " 92234.00c   234.000000 file 0 1 5 1000 0 0 2.530000e-08\n"
    " 92235.00c   235.000000 file2 0 1 3 2000 0 0 2.530000e-08 ptable\n"
    " 92000.00p   233.000000 file3 0 1 4 3000\n";
}

std::string chunkWithCommentLines() {

  return
    "# this is a comment line\n"
    "datapath=/some/path/to/Data\n"
    "# this is a comment line\n"
    "# this is a comment line\n"
    "atomic weight ratios\n"
    "       1   1.00000000\n"
    "    1000   0.99931697    1001   0.99916733    1002   1.99679968    1003   2.99013997\n"
    "                         1004   3.99320563\n"
    "# this is a comment line\n"
    "   92000 235.98412800   92235 233.02478975 1092235 233.02478975\n"
    "\n"
    "# this is a comment line\n"
    "directory\n"
    "# this is a comment line\n"
    " 92234.00c   234.000000 file 0 1 5 1000 0 0 2.530000e-08\n"
    " 92235.00c   235.000000 file2 0 1 3 2000 0 0 +\n"
    "     2.530000e-08 ptable\n"
    "# this is a comment line\n"
    "# this is a comment line\n"
    " 92000.00p   233.000000 file3 0 1 4 3000\n";
}

std::string chunkWithUpperCaseAndTrailingWhitespace() {

  return
    "   DaTaPatH=/some/path/to/Data   \n"
    " atomic WEIGHT ratios                      \n"
    "       1   1.00000000\n"
    "    1000   0.99931697    1001   0.99916733    1002   1.99679968    1003   2.99013997\n"
    "                         1004   3.99320563\n"
    "   92000 235.98412800   92235 233.02478975 1092235 233.02478975\n"
    "\n"
    "  DIRECTory               \n"
    " 92234.00c   234.000000 file 0 1 5 1000 0 0 2.530000e-08\n"
    " 92235.00c   235.000000 file2 0 1 3 2000 0 0 +\n"
    "     2.530000e-08 ptable\n"
    " 92000.00p   233.000000 file3 0 1 4 3000\n";
}

void verifyChunk( const Xsdir& chunk ) {

  CHECK( std::nullopt != chunk.dataPath() );
  CHECK( "/some/path/to/Data" == chunk.dataPath().value() );

  CHECK( 9 == chunk.atomicWeightRatios().size() );
  CHECK_THAT(   1.00000000, WithinRel( chunk.atomicWeightRatios().at( 1 ) ) );
  CHECK_THAT(   0.99931697, WithinRel( chunk.atomicWeightRatios().at( 1000 ) ) );
  CHECK_THAT(   0.99916733, WithinRel( chunk.atomicWeightRatios().at( 1001 ) ) );
  CHECK_THAT(   1.99679968, WithinRel( chunk.atomicWeightRatios().at( 1002 ) ) );
  CHECK_THAT(   2.99013997, WithinRel( chunk.atomicWeightRatios().at( 1003 ) ) );
  CHECK_THAT(   3.99320563, WithinRel( chunk.atomicWeightRatios().at( 1004 ) ) );
  CHECK_THAT( 235.98412800, WithinRel( chunk.atomicWeightRatios().at( 92000 ) ) );
  CHECK_THAT( 233.02478975, WithinRel( chunk.atomicWeightRatios().at( 92235 ) ) );
  CHECK_THAT( 233.02478975, WithinRel( chunk.atomicWeightRatios().at( 1092235 ) ) );

  CHECK_THAT(   1.00000000, WithinRel( chunk.atomicWeightRatio( 1 ) ) );
  CHECK_THAT(   0.99931697, WithinRel( chunk.atomicWeightRatio( 1000 ) ) );
  CHECK_THAT(   0.99916733, WithinRel( chunk.atomicWeightRatio( 1001 ) ) );
  CHECK_THAT(   1.99679968, WithinRel( chunk.atomicWeightRatio( 1002 ) ) );
  CHECK_THAT(   2.99013997, WithinRel( chunk.atomicWeightRatio( 1003 ) ) );
  CHECK_THAT(   3.99320563, WithinRel( chunk.atomicWeightRatio( 1004 ) ) );
  CHECK_THAT( 235.98412800, WithinRel( chunk.atomicWeightRatio( 92000 ) ) );
  CHECK_THAT( 233.02478975, WithinRel( chunk.atomicWeightRatio( 92235 ) ) );
  CHECK_THAT( 233.02478975, WithinRel( chunk.atomicWeightRatio( 1092235 ) ) );

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

std::string chunkWithoutDatapath() {

  return
    "\n"
    "atomic weight ratios\n"
    "       1   1.00000000\n"
    "    1000   0.99931697    1001   0.99916733    1002   1.99679968    1003   2.99013997\n"
    "                         1004   3.99320563\n"
    "   92000 235.98412800   92235 233.02478975 1092235 233.02478975\n"
    "\n"
    "directory\n"
    " 92234.00c   234.000000 file 0 1 5 1000 0 0 2.530000e-08\n"
    " 92235.00c   235.000000 file2 0 1 3 2000 0 0 2.530000e-08 ptable\n"
    " 92000.00p   233.000000 file3 0 1 4 3000\n";
}

void verifyChunkWithoutDatapath( const Xsdir& chunk ) {

  CHECK( std::nullopt == chunk.dataPath() );

  CHECK( 9 == chunk.atomicWeightRatios().size() );
  CHECK_THAT(   1.00000000, WithinRel( chunk.atomicWeightRatios().at( 1 ) ) );
  CHECK_THAT(   0.99931697, WithinRel( chunk.atomicWeightRatios().at( 1000 ) ) );
  CHECK_THAT(   0.99916733, WithinRel( chunk.atomicWeightRatios().at( 1001 ) ) );
  CHECK_THAT(   1.99679968, WithinRel( chunk.atomicWeightRatios().at( 1002 ) ) );
  CHECK_THAT(   2.99013997, WithinRel( chunk.atomicWeightRatios().at( 1003 ) ) );
  CHECK_THAT(   3.99320563, WithinRel( chunk.atomicWeightRatios().at( 1004 ) ) );
  CHECK_THAT( 235.98412800, WithinRel( chunk.atomicWeightRatios().at( 92000 ) ) );
  CHECK_THAT( 233.02478975, WithinRel( chunk.atomicWeightRatios().at( 92235 ) ) );
  CHECK_THAT( 233.02478975, WithinRel( chunk.atomicWeightRatios().at( 1092235 ) ) );

  CHECK_THAT(   1.00000000, WithinRel( chunk.atomicWeightRatio( 1 ) ) );
  CHECK_THAT(   0.99931697, WithinRel( chunk.atomicWeightRatio( 1000 ) ) );
  CHECK_THAT(   0.99916733, WithinRel( chunk.atomicWeightRatio( 1001 ) ) );
  CHECK_THAT(   1.99679968, WithinRel( chunk.atomicWeightRatio( 1002 ) ) );
  CHECK_THAT(   2.99013997, WithinRel( chunk.atomicWeightRatio( 1003 ) ) );
  CHECK_THAT(   3.99320563, WithinRel( chunk.atomicWeightRatio( 1004 ) ) );
  CHECK_THAT( 235.98412800, WithinRel( chunk.atomicWeightRatio( 92000 ) ) );
  CHECK_THAT( 233.02478975, WithinRel( chunk.atomicWeightRatio( 92235 ) ) );
  CHECK_THAT( 233.02478975, WithinRel( chunk.atomicWeightRatio( 1092235 ) ) );

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
