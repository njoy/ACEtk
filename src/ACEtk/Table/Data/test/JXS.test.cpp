#include "catch.hpp"
#include "ACEtk/Table.hpp"

using namespace njoy::ACEtk;

extern Table::Data data;

SCENARIO("JXS"){
  const auto& cdata = data;
  REQUIRE(       1 == data.JXS( 1) );
  REQUIRE( 1634036 == data.JXS(16) );
  REQUIRE(       8 == data.JXS(32) );
  REQUIRE(       1 == cdata.JXS( 1) );
  REQUIRE( 1634036 == cdata.JXS(16) );
  REQUIRE(       8 == cdata.JXS(32) );
#ifndef NDEBUG
  REQUIRE_THROWS( data.JXS( 0) );
  REQUIRE_THROWS( data.JXS(33) );
  REQUIRE_THROWS( cdata.JXS( 0) );
  REQUIRE_THROWS( cdata.JXS(33) );
#endif
}
