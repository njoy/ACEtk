#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing PhotonProduction::Tabulated::Builder" ){
  GIVEN( "parent builder" ){
    ContinuousEnergyNeutron::Builder grandparentBuilder{};
    using ParentBuilder = decltype( 
        grandparentBuilder.photonProduction( 12, 102 ) );
    ParentBuilder parentBuilder{ grandparentBuilder, 12, 102 };

    using TabulatedBuilder = decltype( parentBuilder.tabulated( ) );

    struct TestBuilder : TabulatedBuilder{
      using TabulatedBuilder::construct;
      using TabulatedBuilder::TabulatedBuilder;
    };

    int MT{ 102 };
    std::vector< double > boundaries{ 0.0, 3.0 };
    std::vector< double > schemes{ 2.0, 1.0 };
    std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
    std::vector< double > yields{ 2.1, 2.2, 2.5, 2.5 };
    TestBuilder tb{ grandparentBuilder, MT };

    WHEN( "creating a Tabulated photon production" ){
      tb.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .yields( njoy::utility::copy( yields ) );
      auto tabu = tb.construct();
      tb.add();

      THEN( "the members of Tabulated can be verified" ){
        CHECK( energies == tabu.x );
        CHECK( yields == tabu.y );
      }
    }
    WHEN( "constructing a Tabulated photon production "
          "without all it's components" ){
      CHECK_THROWS( tb.construct() );

      THEN( "an exception is thrown" ){
        tb.energies( njoy::utility::copy( energies ) );
        CHECK_THROWS( tb.construct() );
      }
      THEN( "an exception is thrown" ){
        tb.yields( njoy::utility::copy( yields ) );
        CHECK_THROWS( tb.construct() );
      }
    }
  } // GIVEN
} // SCENARIO

