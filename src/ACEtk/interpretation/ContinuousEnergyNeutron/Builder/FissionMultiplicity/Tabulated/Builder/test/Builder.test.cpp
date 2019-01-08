#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing FissionMultiplicity::Tabulated::Builder" ){
  GIVEN( "parent builder" ){
    std::string nuType{ "delayed" };
    ContinuousEnergyNeutron::Builder grandparentBuilder{};
    using ParentBuilder = decltype( 
        grandparentBuilder.fissionMultiplicity( nuType ) );
    ParentBuilder parentBuilder{ grandparentBuilder, nuType };

    using TabulatedBuilder = decltype( parentBuilder.tabulated( ) );

    struct TestBuilder : TabulatedBuilder{
      using TabulatedBuilder::construct;
      using TabulatedBuilder::TabulatedBuilder;
    };

    std::vector< int > boundaries{ 0, 3 };
    std::vector< int > schemes{ 2, 1 };
    std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
    std::vector< double > multiplicities{ 2.1, 2.2, 2.5, 2.5 };
    TestBuilder tb{ grandparentBuilder, nuType };

    WHEN( "creating a Tabulated fission multiplicity" ){
      tb.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .multiplicities( njoy::utility::copy( multiplicities ) );
      auto tabu = tb.construct();
      tb.add();

      THEN( "the members of Tabulated can be verified" ){
        CHECK( energies == tabu.x );
        CHECK( multiplicities == tabu.y );
      }
    }
    WHEN( "constructing a Tabulated fission multiplicity "
          "without all it's components" ){
      CHECK_THROWS( tb.construct() );

      THEN( "an exception is thrown" ){
        tb.energies( njoy::utility::copy( energies ) );
        CHECK_THROWS( tb.construct() );
      }
      THEN( "an exception is thrown" ){
        tb.multiplicities( njoy::utility::copy( multiplicities ) );
        CHECK_THROWS( tb.construct() );
      }
    }
  } // GIVEN
} // SCENARIO

