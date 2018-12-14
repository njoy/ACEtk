#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::details::verify;

SCENARIO( "Testing sorted verification" ){
  GIVEN( "containers" ){
    std::vector< double > normalized{ 0.1, 0.4, 0.3, 0.2 };
    std::vector< double > negative{ -0.1, 0.4, 0.6, 1.0 };
    std::vector< double > unsortedVector{ 1.0, 3.0, 2.0, 4.0 };

    WHEN( "constructing from initializer list" ){
    }

  } // GIVEN

} // SCENARIO
