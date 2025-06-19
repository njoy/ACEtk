// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/Table.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using Header = Table::Header;
using Header201 = Table::Header201;
using Data = Table::Data;

std::string chunk();
std::string chunkWith200Header();
std::string chunkWith201Header();
void verifyChunk( const Table& );
void verifyHeader( const Table& );
void verifyHeader201( const Table& );

SCENARIO( "Table" ) {

  GIVEN( "valid data for a Table instance with an original header" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      Header header( "92238.80c", 236.0058, 2.5301E-08, "12/13/12",
                     "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)",
                     "mat9237" );

      Data data( {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }},
                 {{ 15., 14., 13., 12., 11., 10., 9., 8.,
                    7., 6., 5., 4., 3., 2., 1., 0. }},
                 {{  6, 33074, 1595, 132, 46, 814, 2, 0,
                     0,     0,    0,   0,  0,   0, 0, 9 }},
                 {{       1,  788721,  788768,  788815,
                     788862,  788909,  788956, 1270743,
                    1270789, 1363882, 1363927, 1475750,
                    1633494, 1633500, 1633506, 1634036,
                    1634042, 1634042, 1634048, 1637218,
                     789147, 1637220, 1464171, 1465923,
                    1465934, 1465976, 1465982,       0,
                          0,       0,       0,       8 }},
                 { 1.00000000000E+00, 1.03125000000E+00,
                   1.06250000000E+00, 1.09375000000E+00,
                   1.12500000000E+00, 1.15625000000E+00 } );

      Table chunk( std::move( header ), std::move( data ) );

      THEN( "a Table can be constructed and members can be tested" ) {

        verifyHeader( chunk );
        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with the original header" ) {

      State< std::string::iterator > state{ 1, string.begin(), string.end() };
      Table chunk( state );

      THEN( "a Data can be constructed and members can be tested" ) {

        verifyHeader( chunk );
        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed with the normal header" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a Table instance with a 201 header" ) {

    std::string string = chunkWith201Header();

    WHEN( "the data is given explicitly" ) {

      Header201 header201(

        "92238.800nc", "ENDF/B-VIII.0", 236.0058, 2.5301E-08, "2018-05-01",
        { " 92238.80c  236.005800  2.5301E-08   12/13/12",
          "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237" }
      );

      Data data( {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }},
                 {{ 15., 14., 13., 12., 11., 10., 9., 8.,
                    7., 6., 5., 4., 3., 2., 1., 0. }},
                 {{  6, 33074, 1595, 132, 46, 814, 2, 0,
                     0,     0,    0,   0,  0,   0, 0, 9 }},
                 {{       1,  788721,  788768,  788815,
                     788862,  788909,  788956, 1270743,
                    1270789, 1363882, 1363927, 1475750,
                    1633494, 1633500, 1633506, 1634036,
                    1634042, 1634042, 1634048, 1637218,
                     789147, 1637220, 1464171, 1465923,
                    1465934, 1465976, 1465982,       0,
                          0,       0,       0,       8 }},
                 { 1.00000000000E+00, 1.03125000000E+00,
                   1.06250000000E+00, 1.09375000000E+00,
                   1.12500000000E+00, 1.15625000000E+00 } );

      Table chunk( std::move( header201 ), std::move( data ) );

      THEN( "a Table can be constructed and members can be tested" ) {

        verifyHeader201( chunk );
        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with the 2.0.1 header" ) {

      State< std::string::iterator > state{ 1, string.begin(), string.end() };
      Table chunk( state );

      THEN( "a Data can be constructed and members can be tested" ) {

        verifyHeader201( chunk );
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
    "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237\n"
    "      0 15.0000000      1 14.0000000      2 13.0000000      3 12.0000000\n"
    "      4 11.0000000      5 10.0000000      6  9.0000000      7  8.0000000\n"
    "      8  7.0000000      9  6.0000000     10  5.0000000     11  4.0000000\n"
    "     12  3.0000000     13  2.0000000     14  1.0000000     15  0.0000000\n"
    "        6    33074     1595      132       46      814        2        0\n"
    "        0        0        0        0        0        0        0        9\n"
    "        1   788721   788768   788815   788862   788909   788956  1270743\n"
    "  1270789  1363882  1363927  1475750  1633494  1633500  1633506  1634036\n"
    "  1634042  1634042  1634048  1637218   789147  1637220  1464171  1465923\n"
    "  1465934  1465976  1465982        0        0        0        0        8\n"
    "  1.000000000000E+00  1.031250000000E+00  1.062500000000E+00  1.093750000000E+00\n"
    "  1.125000000000E+00  1.156250000000E+00\n";
}

void verifyChunk( const Table& chunk ) {

  CHECK( 16 == chunk.data().IZ().size() );
  CHECK( 0 == chunk.data().IZ( 1 ) );
  CHECK( 1 == chunk.data().IZ( 2 ) );
  CHECK( 2 == chunk.data().IZ( 3 ) );
  CHECK( 3 == chunk.data().IZ( 4 ) );
  CHECK( 4 == chunk.data().IZ( 5 ) );
  CHECK( 5 == chunk.data().IZ( 6 ) );
  CHECK( 6 == chunk.data().IZ( 7 ) );
  CHECK( 7 == chunk.data().IZ( 8 ) );
  CHECK( 8 == chunk.data().IZ( 9 ) );
  CHECK( 9 == chunk.data().IZ( 10 ) );
  CHECK( 10 == chunk.data().IZ( 11 ) );
  CHECK( 11 == chunk.data().IZ( 12 ) );
  CHECK( 12 == chunk.data().IZ( 13 ) );
  CHECK( 13 == chunk.data().IZ( 14 ) );
  CHECK( 14 == chunk.data().IZ( 15 ) );
  CHECK( 15 == chunk.data().IZ( 16 ) );

  CHECK( 16 == chunk.data().AW().size() );
  CHECK( 15 == chunk.data().AW( 1 ) );
  CHECK( 14 == chunk.data().AW( 2 ) );
  CHECK( 13 == chunk.data().AW( 3 ) );
  CHECK( 12 == chunk.data().AW( 4 ) );
  CHECK( 11 == chunk.data().AW( 5 ) );
  CHECK( 10 == chunk.data().AW( 6 ) );
  CHECK( 9 == chunk.data().AW( 7 ) );
  CHECK( 8 == chunk.data().AW( 8 ) );
  CHECK( 7 == chunk.data().AW( 9 ) );
  CHECK( 6 == chunk.data().AW( 10 ) );
  CHECK( 5 == chunk.data().AW( 11 ) );
  CHECK( 4 == chunk.data().AW( 12 ) );
  CHECK( 3 == chunk.data().AW( 13 ) );
  CHECK( 2 == chunk.data().AW( 14 ) );
  CHECK( 1 == chunk.data().AW( 15 ) );
  CHECK( 0 == chunk.data().AW( 16 ) );

  CHECK( 16 == chunk.data().NXS().size() );
  CHECK( 6 == chunk.data().NXS( 1 ) );
  CHECK( 33074 == chunk.data().NXS( 2 ) );
  CHECK( 1595 == chunk.data().NXS( 3 ) );
  CHECK( 132 == chunk.data().NXS( 4 ) );
  CHECK( 46 == chunk.data().NXS( 5 ) );
  CHECK( 814 == chunk.data().NXS( 6 ) );
  CHECK( 2 == chunk.data().NXS( 7 ) );
  CHECK( 0 == chunk.data().NXS( 8 ) );
  CHECK( 0 == chunk.data().NXS( 9 ) );
  CHECK( 0 == chunk.data().NXS( 10 ) );
  CHECK( 0 == chunk.data().NXS( 11 ) );
  CHECK( 0 == chunk.data().NXS( 12 ) );
  CHECK( 0 == chunk.data().NXS( 13 ) );
  CHECK( 0 == chunk.data().NXS( 14 ) );
  CHECK( 0 == chunk.data().NXS( 15 ) );
  CHECK( 9 == chunk.data().NXS( 16 ) );

  CHECK( 32 == chunk.data().JXS().size() );
  CHECK( 1 == chunk.data().JXS( 1 ) );
  CHECK( 788721 == chunk.data().JXS( 2 ) );
  CHECK( 788768 == chunk.data().JXS( 3 ) );
  CHECK( 788815 == chunk.data().JXS( 4 ) );
  CHECK( 788862 == chunk.data().JXS( 5 ) );
  CHECK( 788909 == chunk.data().JXS( 6 ) );
  CHECK( 788956 == chunk.data().JXS( 7 ) );
  CHECK( 1270743 == chunk.data().JXS( 8 ) );
  CHECK( 1270789 == chunk.data().JXS( 9 ) );
  CHECK( 1363882 == chunk.data().JXS( 10 ) );
  CHECK( 1363927 == chunk.data().JXS( 11 ) );
  CHECK( 1475750 == chunk.data().JXS( 12 ) );
  CHECK( 1633494 == chunk.data().JXS( 13 ) );
  CHECK( 1633500 == chunk.data().JXS( 14 ) );
  CHECK( 1633506 == chunk.data().JXS( 15 ) );
  CHECK( 1634036 == chunk.data().JXS( 16 ) );
  CHECK( 1634042 == chunk.data().JXS( 17 ) );
  CHECK( 1634042 == chunk.data().JXS( 18 ) );
  CHECK( 1634048 == chunk.data().JXS( 19 ) );
  CHECK( 1637218 == chunk.data().JXS( 20 ) );
  CHECK( 789147 == chunk.data().JXS( 21 ) );
  CHECK( 1637220 == chunk.data().JXS( 22 ) );
  CHECK( 1464171 == chunk.data().JXS( 23 ) );
  CHECK( 1465923 == chunk.data().JXS( 24 ) );
  CHECK( 1465934 == chunk.data().JXS( 25 ) );
  CHECK( 1465976 == chunk.data().JXS( 26 ) );
  CHECK( 1465982 == chunk.data().JXS( 27 ) );
  CHECK( 0 == chunk.data().JXS( 28 ) );
  CHECK( 0 == chunk.data().JXS( 29 ) );
  CHECK( 0 == chunk.data().JXS( 30 ) );
  CHECK( 0 == chunk.data().JXS( 31 ) );
  CHECK( 8 == chunk.data().JXS( 32 ) );

  CHECK( 6 == chunk.data().XSS().size() );
  CHECK_THAT( 1.00000000000E+00, WithinRel( chunk.data().XSS( 1 ) ) );
  CHECK_THAT( 1.03125000000E+00, WithinRel( chunk.data().XSS( 2 ) ) );
  CHECK_THAT( 1.06250000000E+00, WithinRel( chunk.data().XSS( 3 ) ) );
  CHECK_THAT( 1.09375000000E+00, WithinRel( chunk.data().XSS( 4 ) ) );
  CHECK_THAT( 1.12500000000E+00, WithinRel( chunk.data().XSS( 5 ) ) );
  CHECK_THAT( 1.15625000000E+00, WithinRel( chunk.data().XSS( 6 ) ) );

  auto range = chunk.data().XSS( 1, 2 );
  CHECK( 2 == range.size() );
  CHECK_THAT( 1.00000000000E+00, WithinRel( range[0] ) );
  CHECK_THAT( 1.03125000000E+00, WithinRel( range[1] ) );

  range = chunk.data().XSS( 2, 2 );
  CHECK( 2 == range.size() );
  CHECK_THAT( 1.03125000000E+00, WithinRel( range[0] ) );
  CHECK_THAT( 1.06250000000E+00, WithinRel( range[1] ) );

#ifndef NDEBUG
  CHECK_THROWS( chunk.data().IZ( 0 ) );
  CHECK_THROWS( chunk.data().IZ( 17 ) );

  CHECK_THROWS( chunk.data().AW( 0 ) );
  CHECK_THROWS( chunk.data().AW( 17 ) );

  CHECK_THROWS( chunk.data().NXS( 0 ) );
  CHECK_THROWS( chunk.data().NXS( 17 ) );

  CHECK_THROWS( chunk.data().JXS( 0 ) );
  CHECK_THROWS( chunk.data().JXS( 33 ) );

  CHECK_THROWS( chunk.data().XSS( 0 ) );
  CHECK_THROWS( chunk.data().XSS( 7 ) );
#endif
}

void verifyHeader( const Table& chunk ) {

  auto header = std::get< Header >( chunk.header() );
  CHECK( "92238.80c" == header.ZAID() );
  CHECK_THAT( 236.0058, WithinRel( header.AWR() ) );
  CHECK_THAT( 236.0058, WithinRel( header.atomicWeightRatio() ) );
  CHECK_THAT( 2.5301E-08, WithinRel( header.TEMP() ) );
  CHECK_THAT( 2.5301E-08, WithinRel( header.temperature() ) );
  CHECK( "12/13/12" == header.date() );
  CHECK( "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)"
         == header.title() );
  CHECK( "mat9237" == header.material() );
}

void verifyHeader201( const Table& chunk ) {

  auto header = std::get< Header201 >( chunk.header() );
  CHECK( "2.0.1" == header.VERS() );
  CHECK( "2.0.1" == header.version() );
  CHECK( "92238.800nc" == header.ZAID() );
  CHECK_THAT( 236.0058, WithinRel( header.AWR() ) );
  CHECK_THAT( 236.0058, WithinRel( header.atomicWeightRatio() ) );
  CHECK_THAT( 2.5301E-08, WithinRel( header.TEMP() ) );
  CHECK_THAT( 2.5301E-08, WithinRel( header.temperature() ) );
  CHECK( "2018-05-01" == header.date() );
  CHECK( " 92238.80c  236.005800  2.5301E-08   12/13/12" == header.comments()[0] );
  CHECK( "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237"
         == header.comments()[1] );
}

std::string chunkWith200Header() {

  return
    "2.0.0     92238.710nc              ENDFB-VII.1\n"
    "236.005800 2.5301E-08 12/13/12     3\n"
    "some additional comments on this file\n"
    " 92238.80c  236.005800  2.5301E-08   12/13/12\n"
    "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237\n"
    "      0 15.0000000      1 14.0000000      2 13.0000000      3 12.0000000\n"
    "      4 11.0000000      5 10.0000000      6  9.0000000      7  8.0000000\n"
    "      8  7.0000000      9  6.0000000     10  5.0000000     11  4.0000000\n"
    "     12  3.0000000     13  2.0000000     14  1.0000000     15  0.0000000\n"
    "        6    33074     1595      132       46      814        2        0\n"
    "        0        0        0        0        0        0        0        9\n"
    "        1   788721   788768   788815   788862   788909   788956  1270743\n"
    "  1270789  1363882  1363927  1475750  1633494  1633500  1633506  1634036\n"
    "  1634042  1634042  1634048  1637218   789147  1637220  1464171  1465923\n"
    "  1465934  1465976  1465982        0        0        0        0        8\n"
    "  1.000000000000E+00  1.031250000000E+00  1.062500000000E+00  1.093750000000E+00\n"
    "  1.125000000000E+00  1.156250000000E+00\n";
}

std::string chunkWith201Header() {

  return
    "2.0.1                   92238.800nc            ENDF/B-VIII.0\n"
    "  236.005800   2.5301E-08 2018-05-01          2\n"
    " 92238.80c  236.005800  2.5301E-08   12/13/12\n"
    "U238 ENDF71x (jlconlin)  Ref. see jlconlin (ref 09/10/2012  10:00:53)    mat9237\n"
    "      0 15.0000000      1 14.0000000      2 13.0000000      3 12.0000000\n"
    "      4 11.0000000      5 10.0000000      6  9.0000000      7  8.0000000\n"
    "      8  7.0000000      9  6.0000000     10  5.0000000     11  4.0000000\n"
    "     12  3.0000000     13  2.0000000     14  1.0000000     15  0.0000000\n"
    "        6    33074     1595      132       46      814        2        0\n"
    "        0        0        0        0        0        0        0        9\n"
    "        1   788721   788768   788815   788862   788909   788956  1270743\n"
    "  1270789  1363882  1363927  1475750  1633494  1633500  1633506  1634036\n"
    "  1634042  1634042  1634048  1637218   789147  1637220  1464171  1465923\n"
    "  1465934  1465976  1465982        0        0        0        0        8\n"
    "  1.000000000000E+00  1.031250000000E+00  1.062500000000E+00  1.093750000000E+00\n"
    "  1.125000000000E+00  1.156250000000E+00\n";
}
