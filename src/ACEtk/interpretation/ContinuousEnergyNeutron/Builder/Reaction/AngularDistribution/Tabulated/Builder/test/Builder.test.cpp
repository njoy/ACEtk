#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"
using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing AngularDistribution::Builder::Tabulated::Builder" ){
  using grandparentBuilder = ContinuousEnergyNeutron::Builder;
  grandparentBuilder grandparentBuilder{};

  auto reacBuilder = parentBuilder.reaction( 22 );
  using TabBuilder = decltype( reacBuilder.angularDistribution().tabulated() );

  struct TestBuilder : public TabBuilder {
    using TabBuilder::construct;
    using TabBuilder::TabBuilder;
  };

  std::vector< double > cosine{ 1.0, 2.0, 3.0 };
  std::vector< double > pdf{ 0.1, 0.5, 0.4 };
  std::vector< double > cdf{ 0.1, 0.6, 1.0 };

  TestBuilder tb{ reacBuilder };
  GIVEN( "valid inputs" ){

    tb.cosineGrid( njoy::utility::copy( cosine ) )
      .pdf( njoy::utility::copy( pdf ) )
      .cdf( njoy::utility::copy( cdf ) );

    THEN( "the values can be verified" ){
      auto tabulated = tb.construct();
    }
  } // GIVEN
  GIVEN( "invalid inputs" ){
  } // GIVEN
} // SCENARIO
