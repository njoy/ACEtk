#include "catch.hpp"
#include "ACEtk/Table.hpp"

using namespace njoy::ACEtk;

extern Table::Data data;

SCENARIO("NXS"){
  const auto& cdata = data;
  REQUIRE( 84 == data.NXS( 1) );
  REQUIRE(  2 == data.NXS( 7) );
  REQUIRE(  9 == data.NXS(16) );
  REQUIRE( 84 == cdata.NXS( 1) );
  REQUIRE(  2 == cdata.NXS( 7) );
  REQUIRE(  9 == cdata.NXS(16) );
#ifndef NDEBUG
  REQUIRE_THROWS( data.NXS( 0) );
  REQUIRE_THROWS( data.NXS(17) );
  REQUIRE_THROWS( cdata.NXS( 0) );
  REQUIRE_THROWS( cdata.NXS(17) );
#endif
}
