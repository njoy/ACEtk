#include "catch.hpp"
#include "ACEtk/Table.hpp"

using namespace njoy::ACEtk;

namespace {

class Data : public Table::Data {
public:
  using Parse = Table::Data::Parse;
};

}

SCENARIO("IZAW parsing"){
  SECTION("A correct IZAW"){
    std::string IZAW =
      "      0         0.      1         1.      2         2.      3         3.\n"
      "      4         4.      5         5.      6         6.      7         7.\n"
      "      8         8.      9         9.     10        10.     11        11.\n"
      "     12        12.     13        13.     14        14.     15        15.\n";

    State< std::string::iterator > s{ 1, IZAW.begin(), IZAW.end() };
    auto result = Data::Parse::IZAW( s );
    REQUIRE( s.lineNumber == 5 );
    int n = 0;
    RANGES_FOR ( auto entry, ranges::view::zip( result.first,
                                                result.second ) ) {
      REQUIRE( entry.first == n );
      REQUIRE( entry.second == Approx(n) );
      ++n;
    }
  }

  SECTION("an incorrect IZAW"){
    std::string IZAW =
      "      0         0.      1         1.      2         2.      3         3.\n"
      "      4         a.      5         5.      6         6.      7         7.\n"
      "      8         8.      9         9.     10        10.     11        11.\n"
      "     12        12.     13        13.     14        14.     15        15.\n";

    State< std::string::iterator > s{ 1, IZAW.begin(), IZAW.end() };
    REQUIRE_THROWS( Data::Parse::IZAW( s ) );
  }
}
