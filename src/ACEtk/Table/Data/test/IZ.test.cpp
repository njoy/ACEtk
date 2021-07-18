#include "catch.hpp"
#include "ACEtk/Table.hpp"

using namespace njoy::ACEtk;

extern Table::Data data;

SCENARIO("IZ"){
  const auto& cdata = data;
  REQUIRE( 0 == data.IZ( 1) );
  REQUIRE( 0 == data.IZ(16) );
  REQUIRE( 0 == cdata.IZ( 1) );
  REQUIRE( 0 == cdata.IZ(16) );
#ifndef NDEBUG
  REQUIRE_THROWS( data.IZ( 0) );
  REQUIRE_THROWS( data.IZ(17) );
  REQUIRE_THROWS( cdata.IZ( 0) );
  REQUIRE_THROWS( cdata.IZ(17) );
#endif
}
