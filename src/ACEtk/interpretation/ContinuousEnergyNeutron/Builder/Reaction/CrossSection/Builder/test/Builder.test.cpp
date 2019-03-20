#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing Reaction::CrossSection::Builder" ){
  ContinuousEnergyNeutron::Builder topBuilder{};
  using ReacBuilder = decltype( topBuilder.reaction( 102 ) );

  ReacBuilder reacBuilder{ topBuilder, 102 };

  using XSBuilder = decltype( reacBuilder.crossSection( ) );

  struct TestBuilder : public XSBuilder{
    using XSBuilder::construct;
    using XSBuilder::XSBuilder;
  };

  std::vector< double > energyGrid{ 4.0, 5.0, 6.0 };
  auto grid = Table::slice( energyGrid );
  std::vector< double > XS{ 1.0, 2.0, 3.0 };

  TestBuilder tb{ reacBuilder };

  GIVEN( "valid inputs" ){
    WHEN( "constructing a cross section reaction without "
         "a parent energyGrid" ){

      tb.values( njoy::utility::copy( XS ) )
        .energyGrid( grid );

      auto xs = tb.construct();

      THEN( "the members of the cross section can be verified" ){
        CHECK( XS == xs.values );
        CHECK( ranges::equal( grid, xs.energyGrid ) );
      }
    }
  } // GIVEN valid

  GIVEN( "invalid data" ){
    WHEN( "two few cross section values" ){
      std::vector< double > values{ 1.0, 2.0 };
      tb.values( values )
        .energyGrid( grid );

      CHECK_THROWS_AS( tb.construct(), std::range_error& );
    }
    WHEN( "too many cross section values" ){
      std::vector< double > values{ 1.0, 2.0, 3.0, 4.0 };
      tb.values( values )
        .energyGrid( grid );

      CHECK_THROWS_AS( tb.construct(), std::range_error& );
    }
  } // GIVEN
} // SCENARIO
