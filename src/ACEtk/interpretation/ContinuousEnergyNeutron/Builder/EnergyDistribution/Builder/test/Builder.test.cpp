#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::Builder" ){
  ContinuousEnergyNeutron::Builder CENBuilder;
  using ParentBuilder = decltype( CENBuilder.reaction( 14 ) );

  ParentBuilder parentBuilder{ CENBuilder, 14 };
  using EDBuilder = decltype( parentBuilder.energyDistribution() );

  struct TestBuilder : public EDBuilder {
    using EDBuilder::construct;
    using EDBuilder::EDBuilder;
  };

  TestBuilder tb{ parentBuilder };

  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
  std::vector< double > probabilities{ 0.1, 0.2, 0.5, 0.2 };

  GIVEN( "valid inputs" ){
    tb.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) );

    THEN( "a law can be given" ){
      std::vector< double > eout_v{ 1.1, 1.2, 1.3 };
      std::array< double, 3 > eout_a{ 1.1, 1.2, 1.4 };

      tb.tabularEquiprobableEnergyBins()
          .boundaries( njoy::utility::copy( boundaries ) )
          .schemes( njoy::utility::copy( schemes ) )
          .energies( njoy::utility::copy( energies ) )
          .outgoingEnergyTable( njoy::utility::copy( eout_v ) )
          .outgoingEnergyTable( njoy::utility::copy( eout_a ) )
          .outgoingEnergyTable( njoy::utility::copy( eout_a ) )
          .outgoingEnergyTable( njoy::utility::copy( eout_a ) )
          .add();

      auto ED = tb.construct();

      THEN( "the values of the distribution can be checked" ){
        auto parameters = ED.tab1.parameters;
        CHECK( ranges::equal( boundaries, parameters->first ) );
        CHECK( ranges::equal( schemes, parameters->second ) );
        CHECK( ranges::equal( energies, ED.tab1.x ) );
        CHECK( probabilities == ED.tab1.y );
      }
    }
  } // GIVEN
  GIVEN( "invalid inputs" ){
    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
    WHEN( "probabilities are negative" ){
      std::vector< double > probabilities{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.probabilities( njoy::utility::copy( probabilities ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
  }
} // SCENARIO
