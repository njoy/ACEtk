#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing Reaction::EnergyDependentNeutronYields::Builder" ){
  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  ParentBuilder parentBuilder{};

  auto reacBuilder = parentBuilder.reaction( 22 );
  using EDNYBuilder = decltype( reacBuilder.energyDependentNeutronYields() );

  struct TestBuilder : public EDNYBuilder {
    using EDNYBuilder::construct;
    using EDNYBuilder::EDNYBuilder;
  };

  TestBuilder tb{ reacBuilder };

  GIVEN( "valid inputs" ){
    std::vector< int > boundaries{ 0, 3 };
    std::vector< int > schemes{ 2, 1 };
    std::vector< double > energies{ 1.0, 2.0 };
    std::vector< double > yields{ 1.45, 2.35 };

    tb.boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) )
      .yields( njoy::utility::copy( yields ) );

    auto tabulated = tb.construct();

    THEN( "the values can be verified" ){
      auto parameters = tabulated.parameters;
      CHECK( ranges::equal( boundaries, parameters->first ) );
      CHECK( ranges::equal( schemes, parameters->second ) );
      CHECK( ranges::equal( energies, tabulated.x ) );
      CHECK( ranges::equal( yields, tabulated.y ) );
    }
  } // GIVEN valid
  GIVEN( "invalid inputs" ){
    WHEN( "yields are negative" ){
      std::vector< double > yields{ 1.0, 2.0, -5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.yields( njoy::utility::copy( yields ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
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
  }
}
