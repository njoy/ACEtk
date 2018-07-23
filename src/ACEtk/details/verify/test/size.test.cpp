#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details;

SCENARIO( "Testing size verification" ){
  GIVEN( "containers" ){
    std::vector< int > size3{ 1, 2, 4 };
    std::vector< int > size4{ 1, 2, 4, 5 };

    REQUIRE_NOTHROW( verify::equalSize( size3, size3 ) );
    REQUIRE_THROWS_AS( verify::equalSize( size4, size3 ), std::range_error );
  } // GIVEN
} // SCENARIO
