#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;
using namespace dimwits;

SCENARIO( "Constructing PhotonProduction angular distribution" ){
  std::vector< double > energyGrid{ 1.1, 1.2, 1.3 };
  std::vector< double > cosineBins{{
    0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10,
        0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.20,
        0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.30,
        0.31, 0.32,

        1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09, 1.10,
        1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19, 1.20,
        1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29, 1.30,
        1.31, 1.32,

        2.01, 2.02, 2.03, 2.04, 2.05, 2.06, 2.07, 2.08, 2.09, 2.10,
        2.11, 2.12, 2.13, 2.14, 2.15, 2.16, 2.17, 2.18, 2.19, 2.20,
        2.21, 2.22, 2.23, 2.24, 2.25, 2.26, 2.27, 2.28, 2.29, 2.30,
        2.31, 2.32
  }};
  GIVEN( "the pieces necessary to build the angular distribution" ){

    ContinuousEnergyNeutron::AngularDistribution::PhotonProduction PP{ 
      energyGrid, cosineBins };

    THEN( "the values can be verified" ){
      CHECK( ranges::equal( energyGrid, PP.energyGrid() ) );
    }
  }
  GIVEN( "invalid photon production angular distribution pieces" ){
    WHEN( "cosine bin size is too small" ){
      cosineBins.pop_back();
      CHECK_THROWS(
        ContinuousEnergyNeutron::AngularDistribution::PhotonProduction( 
          energyGrid, cosineBins ) 
      );
    }
  }
}
