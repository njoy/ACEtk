#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing FissionMultiplicity::Polynomial::Builder" ){
  GIVEN( "parent builder" ){
    ContinuousEnergyNeutron::Builder grandparentBuilder{};
    using ParentBuilder = decltype( grandparentBuilder.fissionMultiplicity() );
    ParentBuilder parentBuilder{ grandparentBuilder };

    using PolynomialBuilder = decltype( parentBuilder.polynomial() );

    struct TestBuilder : PolynomialBuilder{
      using PolynomialBuilder::construct;
      using PolynomialBuilder::PolynomialBuilder;
    };

    std::vector< double > coefficients{ 1.0, 2.0, 5.0, 6.0 };
    TestBuilder tb{ grandparentBuilder };

    WHEN( "creating a Polynomial fission multiplicity" ){
      tb.coefficients( njoy::utility::copy( coefficients ) );
      auto poly = tb.construct();

      THEN( "the coefficients can be verified" ){
        CHECK( coefficients == poly.coefficients );
      }
    }
    WHEN( "creating a Polynomial fission multiplicity without coefficients" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( tb.construct() );
      }
    }
  } // GIVEN
} // SCENARIO

