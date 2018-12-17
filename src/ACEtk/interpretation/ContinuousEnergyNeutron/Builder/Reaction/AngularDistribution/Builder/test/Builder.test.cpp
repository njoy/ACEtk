#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing Builder::Reaction::AngularDistribution::Builder" ){
  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  ParentBuilder parentBuilder{};

  auto reacBuilder = parentBuilder.reaction( 22 );
  using ADBuilder = decltype( reacBuilder.angularDistribution() );

  struct TestBuilder : public ADBuilder {
    using ADBuilder::construct;
    using ADBuilder::ADBuilder;
  };

  std::vector< double > grid{ 1.0, 2.0, 3.0 };

  TestBuilder tb{ reacBuilder };
  GIVEN( "valid inputs" ){
    tb.energyGrid( njoy::utility::copy( grid ) );
    tb.isotropic();
    tb.isotropic();
    tb.isotropic();

    THEN( "the built values can be verified" ){
      auto angDistribution = tb.construct();

      CHECK( ranges::equal( grid, angDistribution.energyGrid ) );
      CHECK( 3 == angDistribution.representations.size() );
    }
  } // GIVEN
  GIVEN( "invalid inputs" ){
    WHEN( "wrong number of representations are given" ){
      tb.energyGrid( njoy::utility::copy( grid ) );
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          tb.construct(),
          std::range_error&
        );
      }
    }
    WHEN( "energy grid isn't postiive" ){
      std::vector< double > grid{ -1.0, 2.0, 3.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          tb.energyGrid( grid ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energy grid isn't sorted" ){
      std::vector< double > grid{ 1.0, 4.0, 3.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          tb.energyGrid( grid ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
  } // GIVEN
} // SCENARIO
