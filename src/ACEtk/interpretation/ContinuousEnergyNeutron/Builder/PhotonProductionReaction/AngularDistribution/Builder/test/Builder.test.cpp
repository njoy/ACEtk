#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing Builder::TotalGammaProduction::Builder" ){
  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  ParentBuilder parentBuilder{};

  auto ppBuilder = parentBuilder.photonProductionReaction( 16, 102 );
  using ADBuilder = decltype( ppBuilder.angularDistribution() );

  struct TestBuilder : public ADBuilder {
    using ADBuilder::construct;
    using ADBuilder::ADBuilder;
  };

  std::vector< double > grid{ 1.0, 2.0, 3.0 };
  std::vector< std::array< double, 33 > > bins{
    { 0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
      0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19,
      0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29,
      0.30, 0.31, 0.32 },

    { 1.00, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09,
      1.10, 1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19,
      1.20, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29,
      1.30, 1.31, 1.32 },

    { 2.00, 2.01, 2.02, 2.03, 2.04, 2.05, 2.06, 2.07, 2.08, 2.09,
      2.10, 2.11, 2.12, 2.13, 2.14, 2.15, 2.16, 2.17, 2.18, 2.19,
      2.20, 2.21, 2.22, 2.23, 2.24, 2.25, 2.26, 2.27, 2.28, 2.29,
      2.30, 2.31, 2.32 }
  };
  TestBuilder tb{ ppBuilder };
  GIVEN( "valid inputs" ){
    WHEN( "building an Angular Distribution" ){
      tb.energyGrid( njoy::utility::copy( grid ) );
      tb.cosineBins( njoy::utility::copy( bins ) );

      THEN( "the values can be verified" ){
        auto angDistribution = tb.construct();

        CHECK( ranges::equal( grid, angDistribution.energyGrid ) );
        CHECK( ranges::equal( bins, angDistribution.cosineBins ) );
      }
    } // WHEN
  } // GIVEN

  GIVEN( "invalid inputs" ){
    WHEN( "energy grid and bins are not the same size" ){
      std::vector< double > grid{ 1.0, 2.0 };
      tb.energyGrid( njoy::utility::copy( grid ) )
        .cosineBins( njoy::utility::copy( bins ) );
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          tb.construct(),
          std::range_error&
        );
      }
    }
    WHEN( "grid isn't all positive" ){
      std::vector< double > grid{ 1.0, 2.0, -3.0 };
      tb.energyGrid( njoy::utility::copy( grid ) )
        .cosineBins( njoy::utility::copy( bins ) );
      THEN( "an exception is thrown" ){
        CHECK_THROWS( tb.construct() );
      }
    }
  }
} // SCENARIO
