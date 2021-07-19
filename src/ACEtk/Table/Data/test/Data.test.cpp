#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/Table.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using Data = Table::Data;

std::string chunk();
void verifyChunk( const Data& );

SCENARIO( "Data" ) {

  GIVEN( "valid data for a Data instance" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly (5 arrays)" ) {

      std::array< int32_t, 16 > IZ = {{ 0, 1, 2, 3, 4, 5, 6, 7,
                                        8, 9, 10, 11, 12, 13, 14, 15 }};
      std::array< double, 16 > AW ={{ 15., 14., 13., 12., 11., 10., 9., 8.,
                                      7., 6., 5., 4., 3., 2., 1., 0. }};
      std::array< int64_t, 16 > NXS = {{  6, 33074, 1595, 132, 46, 814, 2, 0,
                                          0,     0,    0,   0,  0,   0, 0, 9 }};
      std::array< int64_t, 32 > JXS = {{       1,  788721,  788768,  788815,
                                          788862,  788909,  788956, 1270743,
                                         1270789, 1363882, 1363927, 1475750,
                                         1633494, 1633500, 1633506, 1634036,
                                         1634042, 1634042, 1634048, 1637218,
                                          789147, 1637220, 1464171, 1465923,
                                         1465934, 1465976, 1465982,       0,
                                               0,       0,       0,       8 }};
      std::vector< double > XSS = { 1.00000000000E+00, 1.03125000000E+00,
                                    1.06250000000E+00, 1.09375000000E+00,
                                    1.12500000000E+00, 1.15625000000E+00 };

      Table::Data chunk( std::move( IZ ), std::move( AW ), std::move( NXS ),
                         std::move( JXS ), std::move( XSS ) );

      THEN( "a Data can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly (4 arrays)" ) {

      std::pair< std::array< int32_t, 16 >,
                 std::array< double, 16 > > IZAW = {

                   {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }},
                   {{ 15., 14., 13., 12., 11., 10., 9., 8.,
                       7., 6., 5., 4., 3., 2., 1., 0. }}
                 };
      std::array< int64_t, 16 > NXS = {{  6, 33074, 1595, 132, 46, 814, 2, 0,
                                          0,     0,    0,   0,  0,   0, 0, 9 }};
      std::array< int64_t, 32 > JXS = {{       1,  788721,  788768,  788815,
                                          788862,  788909,  788956, 1270743,
                                         1270789, 1363882, 1363927, 1475750,
                                         1633494, 1633500, 1633506, 1634036,
                                         1634042, 1634042, 1634048, 1637218,
                                          789147, 1637220, 1464171, 1465923,
                                         1465934, 1465976, 1465982,       0,
                                               0,       0,       0,       8 }};
      std::vector< double > XSS = { 1.00000000000E+00, 1.03125000000E+00,
                                    1.06250000000E+00, 1.09375000000E+00,
                                    1.12500000000E+00, 1.15625000000E+00 };

      Table::Data chunk( std::move( IZAW ), std::move( NXS ),
                         std::move( JXS ), std::move( XSS ) );

      THEN( "a Data can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::ostringstream oss;
        chunk.print( oss );

        CHECK( oss.str() == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      State< std::string::iterator > state{ 1, string.begin(), string.end() };
      Data chunk( state );

      THEN( "a Data can be constructed and members can be tested" ) {

        verifyChunk( chunk );
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

void verifyChunk( const Data& chunk ) {

  CHECK( 16 == chunk.IZ().size() );
  CHECK( 0 == chunk.IZ( 1 ) );
  CHECK( 1 == chunk.IZ( 2 ) );
  CHECK( 2 == chunk.IZ( 3 ) );
  CHECK( 3 == chunk.IZ( 4 ) );
  CHECK( 4 == chunk.IZ( 5 ) );
  CHECK( 5 == chunk.IZ( 6 ) );
  CHECK( 6 == chunk.IZ( 7 ) );
  CHECK( 7 == chunk.IZ( 8 ) );
  CHECK( 8 == chunk.IZ( 9 ) );
  CHECK( 9 == chunk.IZ( 10 ) );
  CHECK( 10 == chunk.IZ( 11 ) );
  CHECK( 11 == chunk.IZ( 12 ) );
  CHECK( 12 == chunk.IZ( 13 ) );
  CHECK( 13 == chunk.IZ( 14 ) );
  CHECK( 14 == chunk.IZ( 15 ) );
  CHECK( 15 == chunk.IZ( 16 ) );

  CHECK( 16 == chunk.AW().size() );
  CHECK( 15 == chunk.AW( 1 ) );
  CHECK( 14 == chunk.AW( 2 ) );
  CHECK( 13 == chunk.AW( 3 ) );
  CHECK( 12 == chunk.AW( 4 ) );
  CHECK( 11 == chunk.AW( 5 ) );
  CHECK( 10 == chunk.AW( 6 ) );
  CHECK( 9 == chunk.AW( 7 ) );
  CHECK( 8 == chunk.AW( 8 ) );
  CHECK( 7 == chunk.AW( 9 ) );
  CHECK( 6 == chunk.AW( 10 ) );
  CHECK( 5 == chunk.AW( 11 ) );
  CHECK( 4 == chunk.AW( 12 ) );
  CHECK( 3 == chunk.AW( 13 ) );
  CHECK( 2 == chunk.AW( 14 ) );
  CHECK( 1 == chunk.AW( 15 ) );
  CHECK( 0 == chunk.AW( 16 ) );

  CHECK( 16 == chunk.NXS().size() );
  CHECK( 6 == chunk.NXS( 1 ) );
  CHECK( 33074 == chunk.NXS( 2 ) );
  CHECK( 1595 == chunk.NXS( 3 ) );
  CHECK( 132 == chunk.NXS( 4 ) );
  CHECK( 46 == chunk.NXS( 5 ) );
  CHECK( 814 == chunk.NXS( 6 ) );
  CHECK( 2 == chunk.NXS( 7 ) );
  CHECK( 0 == chunk.NXS( 8 ) );
  CHECK( 0 == chunk.NXS( 9 ) );
  CHECK( 0 == chunk.NXS( 10 ) );
  CHECK( 0 == chunk.NXS( 11 ) );
  CHECK( 0 == chunk.NXS( 12 ) );
  CHECK( 0 == chunk.NXS( 13 ) );
  CHECK( 0 == chunk.NXS( 14 ) );
  CHECK( 0 == chunk.NXS( 15 ) );
  CHECK( 9 == chunk.NXS( 16 ) );

  CHECK( 32 == chunk.JXS().size() );
  CHECK( 1 == chunk.JXS( 1 ) );
  CHECK( 788721 == chunk.JXS( 2 ) );
  CHECK( 788768 == chunk.JXS( 3 ) );
  CHECK( 788815 == chunk.JXS( 4 ) );
  CHECK( 788862 == chunk.JXS( 5 ) );
  CHECK( 788909 == chunk.JXS( 6 ) );
  CHECK( 788956 == chunk.JXS( 7 ) );
  CHECK( 1270743 == chunk.JXS( 8 ) );
  CHECK( 1270789 == chunk.JXS( 9 ) );
  CHECK( 1363882 == chunk.JXS( 10 ) );
  CHECK( 1363927 == chunk.JXS( 11 ) );
  CHECK( 1475750 == chunk.JXS( 12 ) );
  CHECK( 1633494 == chunk.JXS( 13 ) );
  CHECK( 1633500 == chunk.JXS( 14 ) );
  CHECK( 1633506 == chunk.JXS( 15 ) );
  CHECK( 1634036 == chunk.JXS( 16 ) );
  CHECK( 1634042 == chunk.JXS( 17 ) );
  CHECK( 1634042 == chunk.JXS( 18 ) );
  CHECK( 1634048 == chunk.JXS( 19 ) );
  CHECK( 1637218 == chunk.JXS( 20 ) );
  CHECK( 789147 == chunk.JXS( 21 ) );
  CHECK( 1637220 == chunk.JXS( 22 ) );
  CHECK( 1464171 == chunk.JXS( 23 ) );
  CHECK( 1465923 == chunk.JXS( 24 ) );
  CHECK( 1465934 == chunk.JXS( 25 ) );
  CHECK( 1465976 == chunk.JXS( 26 ) );
  CHECK( 1465982 == chunk.JXS( 27 ) );
  CHECK( 0 == chunk.JXS( 28 ) );
  CHECK( 0 == chunk.JXS( 29 ) );
  CHECK( 0 == chunk.JXS( 30 ) );
  CHECK( 0 == chunk.JXS( 31 ) );
  CHECK( 8 == chunk.JXS( 32 ) );

  CHECK( 6 == chunk.XSS().size() );
  CHECK( 1.00000000000E+00 == Approx( chunk.XSS( 1 ) ) );
  CHECK( 1.03125000000E+00 == Approx( chunk.XSS( 2 ) ) );
  CHECK( 1.06250000000E+00 == Approx( chunk.XSS( 3 ) ) );
  CHECK( 1.09375000000E+00 == Approx( chunk.XSS( 4 ) ) );
  CHECK( 1.12500000000E+00 == Approx( chunk.XSS( 5 ) ) );
  CHECK( 1.15625000000E+00 == Approx( chunk.XSS( 6 ) ) );

  auto range = chunk.XSS( 1, 2 );
  CHECK( 2 == range.size() );
  CHECK( 1.00000000000E+00 == Approx( range[0] ) );
  CHECK( 1.03125000000E+00 == Approx( range[1] ) );

  range = chunk.XSS( 2, 2 );
  CHECK( 2 == range.size() );
  CHECK( 1.03125000000E+00 == Approx( range[0] ) );
  CHECK( 1.06250000000E+00 == Approx( range[1] ) );

#ifndef NDEBUG
  CHECK_THROWS( chunk.IZ( 0 ) );
  CHECK_THROWS( chunk.IZ( 17 ) );

  CHECK_THROWS( chunk.AW( 0 ) );
  CHECK_THROWS( chunk.AW( 17 ) );

  CHECK_THROWS( chunk.NXS( 0 ) );
  CHECK_THROWS( chunk.NXS( 17 ) );

  CHECK_THROWS( chunk.JXS( 0 ) );
  CHECK_THROWS( chunk.JXS( 33 ) );

  CHECK_THROWS( chunk.XSS( 0 ) );
  CHECK_THROWS( chunk.XSS( 7 ) );
#endif
}
