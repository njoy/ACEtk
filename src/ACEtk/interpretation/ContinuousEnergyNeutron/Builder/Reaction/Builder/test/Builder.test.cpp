#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing ContinuousEnergyNeutron::Builder::Reaction::Builder" ){
  GIVEN( "parent builder" ){
    ContinuousEnergyNeutron::Builder parentBuilder{};
    using ReactionBuilder = decltype( parentBuilder.reaction( 1 ) );

    struct TestBuilder : ReactionBuilder {
      using ReactionBuilder::construct;
      using ReactionBuilder::ReactionBuilder;
    };

    TestBuilder tb{ 14, parentBuilder };

    std::vector< double > energyGrid{ 4.0, 5.0, 6.0 };
    njoy::ACEtk::Table::Slice grid{ energyGrid.begin(), energyGrid.end() };

    WHEN( "creating a Reaction Builder without a parent energyGrid" ){
      std::vector< double > XS{ 1.0, 2.0, 3.0 };

      THEN( "an exception is thrown if no energyGrid is given" ){
        CHECK_THROWS( tb.crossSection( njoy::utility::copy( XS ) ) );
      }

      tb.crossSection( njoy::utility::copy( XS ), grid );
      auto reaction = tb.construct();

      THEN( "the constructed Reaction can be verified" ){
        CHECK( XS == reaction.crossSection );
        CHECK( 14 == reaction.MT );
        CHECK( ranges::equal( energyGrid, reaction.energyGrid ) );
      }
    } // WHEN
    WHEN( "creating a Reaction Builder witha parent energyGrid" ){
      std::vector< double > XS{ 1.0, 2.0, 3.0 };

      parentBuilder.energyGrid( njoy::utility::copy( energyGrid ) );
      THEN( "no exception is thrown if no energyGrid is given" ){
        CHECK_NOTHROW( tb.crossSection( njoy::utility::copy( XS ) ) );
      }

      tb.crossSection( njoy::utility::copy( XS ) );
      auto reaction = tb.construct();

      THEN( "the constructed Reaction can be verified" ){
        CHECK( XS == reaction.crossSection );
        CHECK( 14 == reaction.MT );
        CHECK( ranges::equal( energyGrid, reaction.energyGrid ) );
      }
    } // WHEN
    WHEN( "all the pieces of a Reaction are not present" ){
      CHECK_THROWS( tb.construct() );
    }
  } // GIVEN
} // SCENARIO
