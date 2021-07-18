#include "catch.hpp"
#include "ACEtk/Table.hpp"

using namespace njoy::ACEtk;

namespace {

class Data : public Table::Data {
public:
  using Parse = Table::Data::Parse;
};

}

SCENARIO("JXS parsing"){
  SECTION("A correct JXS"){
    std::string JXS =
      "        1   788721   788768   788815   788862   788909   788956  1270743\n"
      "  1270789  1363882  1363927  1475750  1633494  1633500  1633506  1634036\n"
      "  1634042  1634042  1634048  1637218   789147  1637220  1464171  1465923\n"
      "  1465934  1465976  1465982        0        0        0        0        0\n";

     State< std::string::iterator > s{ 1, JXS.begin(), JXS.end() };
     auto result = Data::Parse::JXS( s );

     REQUIRE( s.lineNumber == 5 );
     REQUIRE( result[0] ==        1 );
     REQUIRE( result[1] ==   788721 );
     REQUIRE( result[2] ==   788768 );
     REQUIRE( result[3] ==   788815 );
     REQUIRE( result[4] ==   788862 );
     REQUIRE( result[5] ==   788909 );
     REQUIRE( result[6] ==   788956 );
     REQUIRE( result[7] ==  1270743 );
     REQUIRE( result[8] ==  1270789 );
     REQUIRE( result[9] ==  1363882 );
     REQUIRE( result[10] == 1363927 );
     REQUIRE( result[11] == 1475750 );
     REQUIRE( result[12] == 1633494 );
     REQUIRE( result[13] == 1633500 );
     REQUIRE( result[14] == 1633506 );
     REQUIRE( result[15] == 1634036 );
     REQUIRE( result[16] == 1634042 );
     REQUIRE( result[17] == 1634042 );
     REQUIRE( result[18] == 1634048 );
     REQUIRE( result[19] == 1637218 );
     REQUIRE( result[20] ==  789147 );
     REQUIRE( result[21] == 1637220 );
     REQUIRE( result[22] == 1464171 );
     REQUIRE( result[23] == 1465923 );
     REQUIRE( result[24] == 1465934 );
     REQUIRE( result[25] == 1465976 );
     REQUIRE( result[26] == 1465982 );
     REQUIRE( result[27] ==       0 );
     REQUIRE( result[28] ==       0 );
     REQUIRE( result[29] ==       0 );
     REQUIRE( result[30] ==       0 );
     REQUIRE( result[31] ==       0 );
  }

  SECTION("A incorrect JXS"){
    std::string JXS =
      "        1   788721   788768   788815   788862   788909   788956  1270743\n"
      "  1270789  1363882  1363927  1475750  1633494  1633500  1633506  1634036\n"
      "  1634042  1634042  1634048     XKCD   789147  1637220  1464171  1465923\n"
      "  1465934  1465976  1465982        0        0     SMBC        0        0\n";
    State< std::string::iterator > s{ 1, JXS.begin(), JXS.end() };
    REQUIRE_THROWS( Data::Parse::JXS( s ) );
  }
}
