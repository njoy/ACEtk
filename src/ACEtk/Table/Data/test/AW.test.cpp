#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

extern Table::Data data;

SCENARIO("AW"){
  const auto& cdata = data; 
  REQUIRE( 0.0 == data.AW( 1) );
  REQUIRE( 0.0 == data.AW(16) );
  REQUIRE( 0.0 == cdata.AW( 1) );
  REQUIRE( 0.0 == cdata.AW(16) );
#ifndef NDEBUG
  REQUIRE_THROWS( data.AW( 0) );
  REQUIRE_THROWS( data.AW(17) );
  REQUIRE_THROWS( cdata.AW( 0) );
  REQUIRE_THROWS( cdata.AW(17) );
#endif
}
