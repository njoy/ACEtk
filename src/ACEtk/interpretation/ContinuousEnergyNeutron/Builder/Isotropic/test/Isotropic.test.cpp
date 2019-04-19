#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing Builder::Isotropic" ){
  constexpr auto checked = details::hasACEify< 
      ContinuousEnergyNeutron::Builder::Isotropic&, double& >::value;
  CHECK( checked );
}
