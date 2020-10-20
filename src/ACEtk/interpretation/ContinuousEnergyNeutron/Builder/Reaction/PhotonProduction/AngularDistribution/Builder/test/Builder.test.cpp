#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing photonProduction" ){
  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  ParentBuilder parentBuilder{};

  auto ppBuilder = parentBuilder.reaction( 102 ).photonProduction( 16 );
  using ADBuilder = decltype( ppBuilder.angularDistribution() );

  struct TestBuilder : public ADBuilder {
    using ADBuilder::construct;
    using ADBuilder::ADBuilder;
  };

  std::vector< double > grid{ 1.0, 2.0, 3.0 };
  std::vector< std::array< double, 33 > > bins{
    {{ 0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
       0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19,
       0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29,
       0.30, 0.31, 0.32 }},
    {{ 0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
       0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19,
       0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29,
       0.30, 0.31, 0.32 }},
    {{ -1.0000, -0.9375, -0.8750, -0.8125, -0.7500, -0.6875, -0.6250, -0.5625,
       -0.5000, -0.4375, -0.3750, -0.3125, -0.2500, -0.1875, -0.1250, -0.0625,
        0.0000,  0.0625,  0.1250,  0.1875,  0.2500,  0.3125,  0.3750,  0.4375,
        0.5000,  0.5625,  0.6250,  0.6875,  0.7500,  0.8125,  0.8750,  0.9375,
        1.0000 }}
  };

  TestBuilder tb{ ppBuilder };
  GIVEN( "valid inputs" ){
    WHEN( "building an Angular Distribution" ){
      tb.energyGrid( njoy::utility::copy( grid ) );
      tb.cosineBins( 0,  njoy::utility::copy( bins[ 0 ] ) );
      // tb.cosineBins( 1,  njoy::utility::copy( bins[ 1 ] ) );
      tb.cosineBins( 2,  njoy::utility::copy( bins[ 2 ] ) );

      THEN( "the values can be verified" ){
        auto angDistribution = tb.construct();

        CHECK( ranges::equal( grid, angDistribution.energyGrid ) );
        CHECK( ranges::equal( bins[ 0 ], angDistribution.cosineBins[ 0 ].value() ) );
        CHECK( std::nullopt == angDistribution.cosineBins[ 1 ] );
        CHECK( ranges::equal( bins[ 2 ], angDistribution.cosineBins[ 2 ].value() ) );

        AND_THEN( "the angular distribution can be aceified" ){
          std::vector< double > aceified{};
          aceified.push_back( 3 );
          aceified |= ranges::action::push_back( grid );
          aceified.push_back( 8 );  // L_C( 0 )
          aceified.push_back( 0 );  // L_C( 1 )
          aceified.push_back( 41 );  // L_C( 2 )
          aceified |= ranges::action::push_back( bins[ 0 ] );
          aceified |= ranges::action::push_back( bins[ 2 ] );

          double LOCB{ 0 };
          Table::Data data{};
          data.JXS()[ 16 ] = 1;
          angDistribution.ACEify( data, LOCB );

          CHECK( ranges::equal( aceified, data.XSS() ) );
        }
      }
    } // WHEN
  } // GIVEN

  GIVEN( "invalid inputs" ){
    WHEN( "grid isn't all positive" ){
      std::vector< double > grid{ -1.0, 2.0, 3.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.energyGrid( njoy::utility::copy( grid ) ),
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
  }
} // SCENARIO
