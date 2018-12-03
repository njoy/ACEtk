#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing ContinuousEnergyNeutron::Builder::Reaction::Builder" ){
  GIVEN( "parent builder" ){
    struct ParentBuilder: public ContinuousEnergyNeutron::Builder{
      using ContinuousEnergyNeutron::Builder::reactions_;
    };
    ParentBuilder parentBuilder{};
    using ReactionBuilder = decltype( parentBuilder.reaction( 14 ) );

    struct TestBuilder : public ReactionBuilder {
      using ReactionBuilder::construct;
      using ReactionBuilder::ReactionBuilder;
    };

    TestBuilder tb{ 14, parentBuilder };

    double Q{ 3.14 };
    std::vector< double > energyGrid{ 4.0, 5.0, 6.0 };
    njoy::ACEtk::Table::Slice grid{ energyGrid.begin(), energyGrid.end() };

    WHEN( "creating a Reaction Builder without a parent energyGrid" ){
      std::vector< double > XS{ 1.0, 2.0, 3.0 };

      THEN( "an exception is thrown if no energyGrid is given" ){
        CHECK_THROWS( tb.crossSection( njoy::utility::copy( XS ) ) );
      }

      tb.Q( Q );
      tb.crossSection( njoy::utility::copy( XS ), grid );
      tb.add();

      THEN( "the constructed Reaction can be verified" ){
        auto reaction = parentBuilder.reactions_[ 14 ];
        CHECK( Q == reaction.Q );
        CHECK( XS == reaction.crossSection );
        CHECK( 14 == reaction.MT );
        CHECK( ranges::equal( energyGrid, reaction.energyGrid ) );

        CHECK( 1 == 
               static_cast< ParentBuilder& >(parentBuilder).reactions_.size() );
      }
    } // WHEN
    WHEN( "creating a Reaction Builder with a parent energyGrid" ){
      std::vector< double > XS{ 1.0, 2.0, 3.0 };

      parentBuilder.energyGrid( njoy::utility::copy( energyGrid ) );
      THEN( "no exception is thrown if no energyGrid is given" ){
        CHECK_NOTHROW( tb.crossSection( njoy::utility::copy( XS ) ) );
      }

      tb.Q( Q );
      tb.crossSection( njoy::utility::copy( XS ) );
      auto reaction = tb.construct();

      THEN( "the constructed Reaction can be verified" ){
        CHECK( Q == reaction.Q );
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
