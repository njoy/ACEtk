#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

struct myObject{
  void ACEify( Table::Data& ){
  }
};

struct myOtherObject{
};

SCENARIO( "Testing ACEify" ){

  CHECK( details::hasACEify< myObject >::value );
  CHECK( not details::hasACEify< myOtherObject >::value );
}
