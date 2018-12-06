#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing ContinuousEnergyNeutron::Builder::Reaction::Builder" ){
  GIVEN( "parent builder" ){
    ContinuousEnergyNeutron::Builder topBuilder{};
    using PPBuilder = decltype( topBuilder.photonProduction( 13, 102 ) );

    std::vector< double > energyGrid{ 4.0, 5.0, 6.0 };
    PPBuilder ppBuilder{ topBuilder, 13, 102 };
    topBuilder.energyGrid( njoy::utility::copy( energyGrid ) );

    using XSBuilder = decltype( ppBuilder.crossSection( ) );

    struct TestBuilder : public XSBuilder{
      using XSBuilder::construct;
      using XSBuilder::XSBuilder;
    };

    int MT{ 102 };
    std::vector< double > XS{ 1.0, 2.0, 3.0 };
    njoy::ACEtk::Table::Slice grid{ energyGrid.begin(), energyGrid.end() };

    WHEN( "constructing a cross section photon production without "
          "a parent energyGrid" ){

      TestBuilder tb{ topBuilder, MT };
      tb.values( njoy::utility::copy( XS ) );
      tb.energies( grid );

      auto xs = tb.construct();

      THEN( "the members of the cross section can be verified" ){
        CHECK( XS == xs.values );
        CHECK( MT == xs.MT );
        CHECK( ranges::equal( grid, xs.energyGrid ) );
      }
    }
    WHEN( "constructing a cross section photon production with"
          "a parent energyGrid" ){

      TestBuilder tb{ topBuilder, MT };
      tb.values( njoy::utility::copy( XS ) );

      auto xs = tb.construct();

      THEN( "the members of the cross section can be verified" ){
        CHECK( XS == xs.values );
        CHECK( MT == xs.MT );
        CHECK( ranges::equal( grid, xs.energyGrid ) );
      }
    }
    WHEN( "constructing a cross section photon production with invalid data" ){
      TestBuilder tb{ topBuilder, MT };
      GIVEN( "too few cross section values" ){
        tb.values( { 1.0, 2.0 } );
        CHECK_THROWS_AS( tb.construct(), std::range_error& );
      }
      GIVEN( "too many cross section values" ){
        tb.values( { 1.0, 2.0, 3.0, 4.0 } );
        CHECK_THROWS_AS( tb.construct(), std::range_error& );
      }
    }
  } // GIVEN
} // SCENARIO
