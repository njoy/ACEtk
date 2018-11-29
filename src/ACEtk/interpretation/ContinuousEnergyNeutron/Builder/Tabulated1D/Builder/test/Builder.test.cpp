#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing 1DTabulationBuilder" ){
  GIVEN( "parent builder" ){

    struct ParentBuilder: public ContinuousEnergyNeutron::Builder{
      using ContinuousEnergyNeutron::Builder::Tabulated1D;
    };
    ParentBuilder parent;
    using Tabulated1DBuilder = 
      ParentBuilder::Tabulated1D::Builder< ParentBuilder >;

    struct TestBuilder : Tabulated1DBuilder{
      using Tabulated1DBuilder::construct;
      using Tabulated1DBuilder::Tabulated1DBuilder;
    };

    std::vector< double > boundaries{ 0.0, 3.0 };
    std::vector< double > schemes{ 2.0, 1.0 };
    std::vector< double > x{ 1.0, 2.0, 5.0, 6.0 };
    std::vector< double > y{ 2.1, 2.2, 2.5, 2.5 };
    TestBuilder tb{ parent };

    WHEN( "creating a Tabulated1D" ){
      tb.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .x( njoy::utility::copy( x ) )
        .y( njoy::utility::copy( y ) );
      auto tabu = tb.construct();

      THEN( "the members of Tabulated1D can be verified" ){
        CHECK( x == tabu.x );
        CHECK( y == tabu.y );
      }
    }
    WHEN( "constructing a Tabulated1D fission multiplicity "
          "without all it's components" ){
      CHECK_THROWS( tb.construct() );

      THEN( "an exception is thrown" ){
        tb.x( njoy::utility::copy( x ) );
        CHECK_THROWS( tb.construct() );
      }
      THEN( "an exception is thrown" ){
        tb.y( njoy::utility::copy( y ) );
        CHECK_THROWS( tb.construct() );
      }
    }
  } // GIVEN
} // SCENARIO

