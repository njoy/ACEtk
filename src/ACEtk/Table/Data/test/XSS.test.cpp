#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

extern Table::Data data;

SCENARIO("XSS"){
  const auto& cdata = data; 
  REQUIRE( 1.0E-11 == data.XSS( 1) );
  REQUIRE( 1.375E-10 == data.XSS(84) );
  REQUIRE( data.XSS(1, 84)[0]
           == data.XSS( 1) );
  REQUIRE( 1.0E-11 == cdata.XSS( 1) );
  REQUIRE( 1.375E-10 == cdata.XSS(84) );
  REQUIRE( cdata.XSS(1, 84)[0]
           == cdata.XSS( 1) );
#ifndef NDEBUG
  REQUIRE_THROWS( data.XSS( 0) );
  REQUIRE_THROWS( data.XSS(85) );
  REQUIRE_THROWS( cdata.XSS(0, 84) );
  REQUIRE_THROWS( cdata.XSS(1, 85) );
  REQUIRE_THROWS( cdata.XSS( 0) );
  REQUIRE_THROWS( cdata.XSS(85) );
  REQUIRE_THROWS( cdata.XSS(0, 84) );
  REQUIRE_THROWS( cdata.XSS(1, 85) );
#endif
}
