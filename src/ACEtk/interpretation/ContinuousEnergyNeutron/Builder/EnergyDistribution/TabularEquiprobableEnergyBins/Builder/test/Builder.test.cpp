#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::TabularEquiprobableBins::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
    using tEEBBuilder = decltype( 
        parentBuilder.tabularEquiprobableEnergyBins() );

    struct TestBuilder : public tEEBBuilder {
      using tEEBBuilder::construct;
      using tEEBBuilder::tEEBBuilder;
    };


  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
  std::vector< double > eout_v{ 1.1, 1.2, 1.3 };
  std::array< double, 3 > eout_a{{ 1.1, 1.2, 1.4 }};

  TestBuilder tEEB( parentBuilder );

  GIVEN( "valid inputs" ){

    tEEB.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .outgoingEnergyTable( njoy::utility::copy( eout_v ) )
        .outgoingEnergyTable( njoy::utility::copy( eout_a ) );

    CHECK_THROWS(
        tEEB.outgoingEnergyTable( std::vector< double >{ 1.0, 2.0 } ) );

    tEEB.outgoingEnergyTable( njoy::utility::copy( eout_a ) )
        .outgoingEnergyTable( njoy::utility::copy( eout_a ) );
    auto distribution = tEEB.construct();

    THEN( "the values of the distribution can be checked" ){
      auto parameters = distribution.parameters;
      CHECK( ranges::equal( boundaries, parameters->first ) );
      CHECK( ranges::equal( schemes, parameters->second ) );
      CHECK( ranges::equal( energies, distribution.x ) );

      auto y = distribution.y;
      CHECK( eout_v == y[0] );
      CHECK( ranges::equal( eout_a, y[1] ) );
    }
  } // GIVEN

  GIVEN( "invalid inputs" ){
    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tEEB.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tEEB.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
  }
} // SCENARIO

