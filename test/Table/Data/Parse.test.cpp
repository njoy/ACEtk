// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/Table.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;

// exposing the parse functions
class Data : public Table::Data {

public:

  using Parse = Table::Data::Parse;
};

SCENARIO( "Data parsing functions" ) {

  GIVEN( "IZAW" ) {

    WHEN( "a correct IZAW string is parsed" ) {

      std::string IZAW =
      "      0 15.0000000      1 14.0000000      2 13.0000000      3 12.0000000\n"
      "      4 11.0000000      5 10.0000000      6  9.0000000      7  8.0000000\n"
      "      8  7.0000000      9  6.0000000     10  5.0000000     11  4.0000000\n"
      "     12  3.0000000     13  2.0000000     14  1.0000000     15  0.0000000\n";

      State< std::string::iterator > s{ 1, IZAW.begin(), IZAW.end() };
      auto result = Data::Parse::IZAW( s );

      THEN( "the data is parsed correctly" ) {

        CHECK( s.lineNumber == 5 );

        CHECK( 16 == result.first.size() );
        CHECK( 0 == result.first[0] );
        CHECK( 1 == result.first[1] );
        CHECK( 2 == result.first[2] );
        CHECK( 3 == result.first[3] );
        CHECK( 4 == result.first[4] );
        CHECK( 5 == result.first[5] );
        CHECK( 6 == result.first[6] );
        CHECK( 7 == result.first[7] );
        CHECK( 8 == result.first[8] );
        CHECK( 9 == result.first[9] );
        CHECK( 10 == result.first[10] );
        CHECK( 11 == result.first[11] );
        CHECK( 12 == result.first[12] );
        CHECK( 13 == result.first[13] );
        CHECK( 14 == result.first[14] );
        CHECK( 15 == result.first[15] );

        CHECK( 16 == result.second.size() );
        CHECK( 15 == result.second[0] );
        CHECK( 14 == result.second[1] );
        CHECK( 13 == result.second[2] );
        CHECK( 12 == result.second[3] );
        CHECK( 11 == result.second[4] );
        CHECK( 10 == result.second[5] );
        CHECK( 9 == result.second[6] );
        CHECK( 8 == result.second[7] );
        CHECK( 7 == result.second[8] );
        CHECK( 6 == result.second[9] );
        CHECK( 5 == result.second[10] );
        CHECK( 4 == result.second[11] );
        CHECK( 3 == result.second[12] );
        CHECK( 2 == result.second[13] );
        CHECK( 1 == result.second[14] );
        CHECK( 0 == result.second[15] );
      } // THEN
    } // WHEN

    WHEN( "an incorrect IZAW string is parsed" ) {

      std::string IZAW =
      "      0         0.      1         1.      2         2.      3         3.\n"
      "      4         a.      5         5.      6         6.      7         7.\n"
      "      8         8.      9         9.     10        10.     11        11.\n"
      "     12        12.     13        13.     14        14.     15        15.\n";

      THEN( "an exception is thrown" ) {

        State< std::string::iterator > s{ 1, IZAW.begin(), IZAW.end() };
        CHECK_THROWS( Data::Parse::IZAW( s ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "NXS" ) {

    WHEN( "a correct NXS string is parsed" ) {

      std::string NXS =
      "        6    33074     1595      132       46      814        2        0\n"
      "        0        0        0        0        0        0        0        9\n";

      State< std::string::iterator > s{ 1, NXS.begin(), NXS.end() };
      auto result = Data::Parse::NXS( s );

      THEN( "the data is parsed correctly" ) {

        CHECK( 16 == result.size() );
        CHECK( 6 == result[0] );
        CHECK( 33074 == result[1] );
        CHECK( 1595 == result[2] );
        CHECK( 132 == result[3] );
        CHECK( 46 == result[4] );
        CHECK( 814 == result[5] );
        CHECK( 2 == result[6] );
        CHECK( 0 == result[7] );
        CHECK( 0 == result[8] );
        CHECK( 0 == result[9] );
        CHECK( 0 == result[10] );
        CHECK( 0 == result[11] );
        CHECK( 0 == result[12] );
        CHECK( 0 == result[13] );
        CHECK( 0 == result[14] );
        CHECK( 9 == result[15] );
      } // THEN
    } // WHEN

    WHEN( "an incorrect NXS string is parsed" ) {

      std::string NXS =
      "        6    33074     1595      132       46      814        2        0\n"
      "        0        there be dragons here      0        0        0        9\n";

      THEN( "an exception is thrown" ) {

        State< std::string::iterator > s{ 1, NXS.begin(), NXS.end() };
        CHECK_THROWS( Data::Parse::NXS( s ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "JXS" ) {

    WHEN( "a correct JXS string is parsed" ) {

      std::string JXS =
      "        1   788721   788768   788815   788862   788909   788956  1270743\n"
      "  1270789  1363882  1363927  1475750  1633494  1633500  1633506  1634036\n"
      "  1634042  1634042  1634048  1637218   789147  1637220  1464171  1465923\n"
      "  1465934  1465976  1465982        0        0        0        0        8\n";

      State< std::string::iterator > s{ 1, JXS.begin(), JXS.end() };
      auto result = Data::Parse::JXS( s );

      THEN( "the data is parsed correctly" ) {

        CHECK( 32 == result.size() );
        CHECK( 1 == result[0] );
        CHECK( 788721 == result[1] );
        CHECK( 788768 == result[2] );
        CHECK( 788815 == result[3] );
        CHECK( 788862 == result[4] );
        CHECK( 788909 == result[5] );
        CHECK( 788956 == result[6] );
        CHECK( 1270743 == result[7] );
        CHECK( 1270789 == result[8] );
        CHECK( 1363882 == result[9] );
        CHECK( 1363927 == result[10] );
        CHECK( 1475750 == result[11] );
        CHECK( 1633494 == result[12] );
        CHECK( 1633500 == result[13] );
        CHECK( 1633506 == result[14] );
        CHECK( 1634036 == result[15] );
        CHECK( 1634042 == result[16] );
        CHECK( 1634042 == result[17] );
        CHECK( 1634048 == result[18] );
        CHECK( 1637218 == result[19] );
        CHECK( 789147 == result[20] );
        CHECK( 1637220 == result[21] );
        CHECK( 1464171 == result[22] );
        CHECK( 1465923 == result[23] );
        CHECK( 1465934 == result[24] );
        CHECK( 1465976 == result[25] );
        CHECK( 1465982 == result[26] );
        CHECK( 0 == result[27] );
        CHECK( 0 == result[28] );
        CHECK( 0 == result[29] );
        CHECK( 0 == result[30] );
        CHECK( 8 == result[31] );
      } // THEN
    } // WHEN

    WHEN( "an incorrect JXS string is parsed" ) {

      std::string JXS =
      "        1   788721   788768   788815   788862   788909   788956  1270743\n"
      "  1270789  1363882 there be more dragons here  1633500  1633506  1634036\n"
      "  1634042  1634042  1634048  1637218   789147  1637220  1464171  1465923\n"
      "  1465934  1465976  1465982        0        0        0        0        8\n";

      THEN( "an exception is thrown" ) {

        State< std::string::iterator > s{ 1, JXS.begin(), JXS.end() };
        CHECK_THROWS( Data::Parse::JXS( s ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "XSS" ) {

    WHEN( "a correct XSS string is parsed" ) {

      std::string XSS =
      "  1.000000000000E+00  1.031250000000E+00  1.062500000000E+00  1.093750000000E+00\n"
      "  1.125000000000E+00  1.156250000000E+00\n";

      State< std::string::iterator > s{ 1, XSS.begin(), XSS.end() };
      auto result = Data::Parse::XSS( s, 6 );

      THEN( "the data is parsed correctly" ) {

        CHECK( 6 == result.size() );
        CHECK_THAT( 1.00000000000E+00, WithinRel( result[0] ) );
        CHECK_THAT( 1.03125000000E+00, WithinRel( result[1] ) );
        CHECK_THAT( 1.06250000000E+00, WithinRel( result[2] ) );
        CHECK_THAT( 1.09375000000E+00, WithinRel( result[3] ) );
        CHECK_THAT( 1.12500000000E+00, WithinRel( result[4] ) );
        CHECK_THAT( 1.15625000000E+00, WithinRel( result[5] ) );
      } // THEN
    } // WHEN

    WHEN( "an incorrect XSS string is parsed" ) {

      std::string XSS =
      "  1.000000000000E+00  look, more dragons  1.062500000000E+00  1.093750000000E+00\n"
      "  1.125000000000E+00  1.156250000000E+00\n";

      THEN( "an exception is thrown" ) {

        State< std::string::iterator > s{ 1, XSS.begin(), XSS.end() };
        CHECK_THROWS( Data::Parse::XSS( s, 6 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
