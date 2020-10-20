#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details;

SCENARIO( "Verifying neutron yield values" ){
  GIVEN( "valid neutron yields" ){
    std::vector< int > validYields{
      -102, -101, -19, -4, -3, -2, -1, 0, 1, 2, 3, 4, 19, 101, 102
    };
    for( auto yield : validYields ){
      THEN( "no exception is thrown when yield: " + std::to_string( yield ) ){
        CHECK_NOTHROW( verify::neutronYield( yield ) );
      }
    }
  } // GIVEN
  GIVEN( "invalid interpolation parameters" ){
    std::vector< int > invalidYields{ -100, -99, -21, -20, 20, 21, 99, 100 };
    for( auto yield : invalidYields ){
      THEN( "an exception is thrown when yield: " + std::to_string( yield ) ){
        CHECK_THROWS_AS( 
          verify::neutronYield( yield ),
          verify::exceptions::InvalidNeutronYield&
        );
      }
    }
  } // GIVEN invalid
} // SCENARIO

