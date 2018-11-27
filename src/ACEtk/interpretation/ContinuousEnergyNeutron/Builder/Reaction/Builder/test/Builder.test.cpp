#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing ContinuousEnergyNeutron::Builder::Reaction::Builder" ){
  GIVEN( "parent builder" ){
    ContinuousEnergyNeutron::Builder parentBuilder{};
    using ReactionBuilder = decltype( parentBuilder.reaction() );

    struct TestBuilder : ReactionBuilder {
      using ReactionBuilder::construct;
      using ReactionBuilder::ReactionBuilder;
    };

    TestBuilder tb{ parentBuilder };

    WHEN( "creating a Reaction Builder" ){
      std::vector< double > XS{ 1.0, 2.0, 3.0 };


      // auto reaction = tb.crossSection( std::move( XS ) ).construct();
      tb.crossSection( njoy::utility::copy( XS ) );
      auto reaction = tb.construct();

      THEN( "the constructed Reaction can be verified" ){
        CHECK( XS == reaction.crossSection );
      }
    } // WHEN
    WHEN( "all the pieces of a Reaction are not present" ){
      CHECK_THROWS( tb.construct() );
    }
  } // GIVEN
} // SCENARIO
