#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO("Fixed length string"){
  SECTION("default constructor"){
    Table::Header::String<10> s;
    REQUIRE(s == "          " );
  }
  
  SECTION("left flush constructor"){
    Table::Header::String<10> s{"hi"};
    REQUIRE(s == "hi        " );
  }
  
  SECTION("right flush constructor"){
    Table::Header::String<10, true> s{"hi"};
    REQUIRE(s == "        hi" );
  }
  
  SECTION("too big"){
    auto make = []{ return Table::Header::String<5, true>{"012345"}; };
    REQUIRE_THROWS( make() );
  }
  
  SECTION( "convertable to string"){
    Table::Header::String<10> right;
    std::string left = right;
  }
}
