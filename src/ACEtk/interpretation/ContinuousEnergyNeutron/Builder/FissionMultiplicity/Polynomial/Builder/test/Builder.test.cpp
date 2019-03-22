#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing FissionMultiplicity::Polynomial::Builder" ){
  GIVEN( "parent builder" ){
    std::string nuType{ "prompt" };

    ContinuousEnergyNeutron::Builder grandparentBuilder{};
    using ParentBuilder = decltype( 
        grandparentBuilder.fissionMultiplicity( nuType ) );
    ParentBuilder parentBuilder{ grandparentBuilder, nuType };

    using PolynomialBuilder = decltype( 
        parentBuilder.polynomial( ) );

    struct TestBuilder : PolynomialBuilder{
      using PolynomialBuilder::construct;
      using PolynomialBuilder::PolynomialBuilder;
    };

    std::vector< double > coefficients{ 1.0, 2.0, 5.0, 6.0 };
    TestBuilder tb{ grandparentBuilder, nuType };

    WHEN( "creating a Polynomial fission multiplicity" ){
      tb.coefficients( njoy::utility::copy( coefficients ) );
      auto poly = tb.construct();

      THEN( "the coefficients can be verified" ){
        CHECK( coefficients == poly.coefficients );

        AND_THEN( "the contents can be ACE-ified" ){
          auto aceified = ranges::view::concat( 
              ranges::view::single( 1 ), coefficients );

          Table::Data dataTable{};
          poly.ACEify( dataTable );
          CHECK( ranges::equal( aceified, dataTable.XSS() ) );
        }
      }
    }
    WHEN( "creating a Polynomial fission multiplicity without coefficients" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( tb.construct() );
      }
    }
  } // GIVEN
} // SCENARIO

