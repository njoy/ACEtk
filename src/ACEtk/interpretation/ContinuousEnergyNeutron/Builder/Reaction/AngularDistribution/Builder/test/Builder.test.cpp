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

    std::vector< double > cosineBins{
      0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
      0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19,
      0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29,
      0.30, 0.31, 0.32
    };
    int f{1};
    std::vector< double > cosine{ -0.1, 0.5, 0.8 };
    std::vector< double > pdf{ 0.1, 0.5, 0.4 };
    std::vector< double > cdf{ 0.1, 0.6, 1.0 };

    tb.isotropic()
      .tabulated().interpolationFlag( f )
                  .cosineGrid( njoy::utility::copy( cosine ) )
                  .pdf( njoy::utility::copy( pdf ) )
                  .cdf( njoy::utility::copy( cdf ) )
        .add() 
      .equiprobableCosineBins().values( njoy::utility::copy( cosineBins ) )
        .add();

    THEN( "the built values can be verified" ){
      auto angDistribution = tb.construct();

      CHECK( ranges::equal( grid, angDistribution.energyGrid ) );
      CHECK( 3 == angDistribution.representations.size() );

      AND_THEN( "the distribution can be ACEified" ){
        std::vector< double > aceified{};
        aceified.push_back( grid.size() );
        aceified |= ranges::action::push_back( grid );
        aceified.push_back( 0 );    // LC_1
        aceified.push_back( -1 );   // LC_2
        aceified.push_back( 13 );    // LC_3

        Table::Data data{};
        njoy::Log::info( "ACEifying the angular distribution" );
        angDistribution.ACEify( data, 1 );

        njoy::Log::info( "aceified: {}", aceified | ranges::view::all );
        njoy::Log::info( "data.XSS: {}", data.XSS() | ranges::view::all );

        CHECK( ranges::equal( aceified, data.XSS() ) );
      }
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
