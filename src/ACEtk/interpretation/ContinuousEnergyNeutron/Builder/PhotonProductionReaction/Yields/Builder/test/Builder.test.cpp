#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
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
    TestBuilder tb{ parentBuilder, 12, 102 };

    WHEN( "creating a Yields photon production" ){
      tb.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .values( njoy::utility::copy( values ) );

      THEN( "the members of Yields can be verified" ){
        auto tabu = tb.construct();
        auto pair = tabu.tabulated.parameters.value();
        CHECK( boundaries == pair.first );
        CHECK( schemes == pair.second );
        CHECK( energies == tabu.tabulated.x );
        CHECK( values == tabu.tabulated.y );

        AND_THEN( "the contents can be ACE-ified" ){
          std::vector< double > aceified{};
          aceified.push_back( 12 );
          aceified.push_back( 102 );
          aceified.push_back( boundaries.size() );  // N_R
          aceified |= ranges::action::push_back( boundaries );
          aceified |= ranges::action::push_back( schemes );
          aceified.push_back( energies.size() );
          aceified |= ranges::action::push_back( energies );
          aceified |= ranges::action::push_back( values );

          Table::Data data{};
          tabu.ACEify( data );

          CHECK( ranges::equal( aceified, data.XSS() ) );
        }
      }
    }
    WHEN( "constructing a Yields photon production "
          "without all it's components" ){
      CHECK_THROWS( tb.construct() );

      THEN( "an exception is thrown" ){
        tb.energies( njoy::utility::copy( energies ) );
        CHECK_THROWS_AS( tb.construct(), std::bad_optional_access& );
      }
      THEN( "an exception is thrown" ){
        tb.values( njoy::utility::copy( values ) );
        CHECK_THROWS_AS( tb.construct(), std::bad_optional_access& );
      }
    }
  } // GIVEN
} // SCENARIO

