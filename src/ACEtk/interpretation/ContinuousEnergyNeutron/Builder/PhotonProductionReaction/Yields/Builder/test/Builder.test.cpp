#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing PhotonProduction::Yields::Builder" ){
  GIVEN( "parent builder" ){
    ContinuousEnergyNeutron::Builder grandparentBuilder{};
    using ParentBuilder = decltype( 
        grandparentBuilder.photonProductionReaction( 12, 102 ) );
    ParentBuilder parentBuilder{ grandparentBuilder, 12, 102 };

    using YieldsBuilder = decltype( parentBuilder.yields( ) );

    struct TestBuilder : YieldsBuilder{
      using YieldsBuilder::construct;
      using YieldsBuilder::YieldsBuilder;
    };

    std::vector< int > boundaries{ 0, 3 };
    std::vector< int > schemes{ 2, 1 };
    std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
    std::vector< double > values{ 2.1, 2.2, 2.5, 2.5 };
    TestBuilder tb{ parentBuilder };

    WHEN( "creating a Yields photon production" ){
      tb.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .values( njoy::utility::copy( values ) );

      THEN( "the members of Yields can be verified" ){
        auto tabu = tb.construct();
        auto pair = tabu.parameters.value();
        CHECK( boundaries == pair.first );
        CHECK( schemes == pair.second );
        CHECK( energies == tabu.x );
        CHECK( values == tabu.y );
      }
    }
    WHEN( "constructing a Yields photon production "
          "without all it's components" ){
      CHECK_THROWS( tb.construct() );

      THEN( "an exception is thrown" ){
        tb.energies( njoy::utility::copy( energies ) );
        CHECK_THROWS( tb.construct() );
      }
      THEN( "an exception is thrown" ){
        tb.values( njoy::utility::copy( values ) );
        CHECK_THROWS( tb.construct() );
      }
    }
  } // GIVEN
} // SCENARIO
