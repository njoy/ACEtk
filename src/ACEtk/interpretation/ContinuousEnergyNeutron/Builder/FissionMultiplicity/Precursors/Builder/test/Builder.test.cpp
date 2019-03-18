#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing FissionMultiplicity::Precursors::Builder" ){

  ContinuousEnergyNeutron::Builder grandparentBuilder{};
  using ParentBuilder = decltype( 
      grandparentBuilder.fissionMultiplicity( "precursors" ) );
  ParentBuilder parentBuilder{ grandparentBuilder, "precursors" };

  using PreBuilder = decltype( parentBuilder.precursors( ) );

  struct TestBuilder : PreBuilder{
    using PreBuilder::construct;
    using PreBuilder::PreBuilder;
  };

  TestBuilder tb{ grandparentBuilder };

  GIVEN( "valid inputs" ){
    std::vector< double > energies{ 1.0, 2.0 };
    std::vector< double > pdf{ 2.5, 3.7 };
    double l{ 3.14 };

    tb.energies( njoy::utility::copy( energies ) )
      .probabilities( njoy::utility::copy( pdf ) )
      .decayConstant( l );


    auto pre = tb.construct();
    THEN( "the values can be verified" ){

      CHECK( ranges::equal( energies, pre.data.x ) );
      CHECK( ranges::equal( pdf, pre.data.y ) );
      CHECK( l == pre.decayConstant );
    }
  } // GIVEN valid
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
    WHEN( "pdf values are negative" ){
      std::vector< double > pdf{ 1.0, -2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.probabilities( njoy::utility::copy( pdf ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "decay constant is negative" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          tb.decayConstant( -0.01 ),
          std::exception&
        );
      }
    }
  } // GIVEN invalid
} // SCENARIO
