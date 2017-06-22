#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

namespace {

class Data : public Table::Data {
public:
  using Parse = Table::Data::Parse; 
};

}

SCENARIO("NXS parsing"){
  SECTION("A correct NXS"){
     std::string NXS =
      "  1637220    92238   157744       47       45        6        0        6\n"
      "        0       92      238        0        0        0        0        0\n";

     State< std::string::iterator > s{ 1, NXS.begin(), NXS.end() };
     auto result = Data::Parse::NXS( s );
     REQUIRE( s.lineNumber == 3 );
     REQUIRE( result[0] == 1637220 );
     REQUIRE( result[1] ==   92238 );
     REQUIRE( result[2] ==  157744 );
     REQUIRE( result[3] ==      47 );
     REQUIRE( result[4] ==      45 );
     REQUIRE( result[5] ==       6 );
     REQUIRE( result[6] ==       0 );
     REQUIRE( result[7] ==       6 );
     REQUIRE( result[8] ==       0 );
     REQUIRE( result[9] ==      92 );
     REQUIRE( result[10] ==    238 );
     REQUIRE( result[11] ==      0 );
     REQUIRE( result[12] ==      0 );
     REQUIRE( result[13] ==      0 );
     REQUIRE( result[14] ==      0 );
     REQUIRE( result[15] ==      0 );
  }
  
  SECTION("A incorrect NXS"){
    std::string NXS =
      "  1637220    92238   157744       47       45        6        0        6\n"
      "        0       92     I have hands!        0        0        0        0\n";
    State< std::string::iterator > s{ 1, NXS.begin(), NXS.end() };
    REQUIRE_THROWS( Data::Parse::NXS( s ) );
  }
}
