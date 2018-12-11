#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing PhotonProduction::CrossSection::Builder" ){
  GIVEN( "parent builder" ){
    ContinuousEnergyNeutron::Builder topBuilder{};
    using ReacBuilder = decltype( topBuilder.reaction( 102 ) );

    std::vector< double > energyGrid{ 4.0, 5.0, 6.0 };
    ReacBuilder reacBuilder{ topBuilder, 102 };
    reacBuilder.energyGrid( Table::slice( energyGrid ) );

    std::vector< double > XS{ 1.0, 2.0, 3.0 };
    njoy::ACEtk::Table::Slice grid{ energyGrid.begin(), energyGrid.end() };
    using XSBuilder = decltype( reacBuilder.crossSection( ) );

    struct TestBuilder : public XSBuilder{
      using XSBuilder::construct;
      using XSBuilder::XSBuilder;
    };
    WHEN( "constructing a cross section reaction without "
          "a parent energyGrid" ){

      TestBuilder tb{ reacBuilder };
      tb.values( njoy::utility::copy( XS ) );
      tb.energyGrid( grid );

      auto xs = tb.construct();

      THEN( "the members of the cross section can be verified" ){
        CHECK( XS == xs.values );
        CHECK( ranges::equal( grid, xs.energyGrid ) );
      }
    }
    WHEN( "constructing a cross section reaction with"
          "a parent energyGrid" ){

      TestBuilder tb{ reacBuilder };
      tb.values( njoy::utility::copy( XS ) );

      auto xs = tb.construct();

      THEN( "the members of the cross section can be verified" ){
        CHECK( XS == xs.values );
        CHECK( ranges::equal( grid, xs.energyGrid ) );
      }
    }
    WHEN( "constructing a cross section photon production with invalid data" ){
      TestBuilder tb{ reacBuilder };
      GIVEN( "too few cross section values" ){
        std::vector< double > values{ 1.0, 2.0 };
        tb.values( values );
        CHECK_THROWS_AS( tb.construct(), std::range_error& );
      }
      GIVEN( "too many cross section values" ){
        std::vector< double > values{ 1.0, 2.0, 3.0, 4.0 };
        tb.values( values );
        CHECK_THROWS_AS( tb.construct(), std::range_error& );
      }
    }
  } // GIVEN
} // SCENARIO
