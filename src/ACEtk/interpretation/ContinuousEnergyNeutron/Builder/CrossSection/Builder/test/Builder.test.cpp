#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing ContinuousEnergyNeutron::CrossSection" ){
  ContinuousEnergyNeutron::Builder CENBuilder;
  using ParentBuilder = decltype( CENBuilder.reaction( 14 ) );

  ParentBuilder parentBuilder{ CENBuilder, 14 };
  using XSBuilder = decltype( parentBuilder.crossSection() );

  struct TestBuilder : public XSBuilder {
    using XSBuilder::construct;
    using XSBuilder::XSBuilder;
  };

  TestBuilder tb{ parentBuilder };

  std::vector< double > energyGrid{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
  njoy::ACEtk::Table::Slice grid = njoy::ACEtk::Table::slice( energyGrid );
  std::vector< double > XS{ 1.1, 2.1, 3.1, 4.1, 5.1, 6.1 };

  GIVEN( "valid inputs" ){

    WHEN( "using the full energy grid" ){

      tb.values( njoy::utility::copy( XS ) )
        .energyGrid( grid );

      auto crossSection = tb.construct();

      THEN( "the values can be verified" ){
        CHECK( ranges::equal( XS, crossSection.values ) );
        CHECK( ranges::equal( grid, crossSection.energyGrid ) );

        AND_THEN( "the data can be 'aceified'" ){
          std::vector< double > aceified{};
          aceified.push_back( 1 );
          aceified.push_back( XS.size() );
          aceified |= ranges::action::push_back( XS );

          Table::Data data{};
          crossSection.ACEify( data );
          
          CHECK( ranges::equal( aceified, data.XSS() ) );
        }
      }
    }
    WHEN( "using part of the energy grid" ){
      auto sXS = XS | ranges::view::slice( 2, 4 );
      auto sliced = grid | ranges::view::slice( 2, 4 );

      tb.values( njoy::utility::copy( sXS ) )
        .energyGrid( sliced );

      auto crossSection = tb.construct();
      THEN( "the values can be verified" ){
        CHECK( ranges::equal( sXS, crossSection.values ) );
        CHECK( ranges::equal( sliced, crossSection.energyGrid ) );

        AND_THEN( "the data can be 'aceified'" ){
          std::vector< double > aceified{};
          aceified.push_back( 3 );
          aceified.push_back( 2 );
          aceified |= ranges::action::push_back( sXS );

          Table::Data data{};
          crossSection.ACEify( data );

          CHECK( ranges::equal( aceified, data.XSS() ) );
        }
      }
    }
  } // GIVEN valid
  GIVEN( "invalid values" ){
    WHEN( "cross section isn't all positive" ){
      std::vector< double > XS{ -1.1, 2.1, 3.1, 4.1, 5.1, 6.1 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          tb.values( njoy::utility::copy( XS ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energyGrid isn't all positive" ){
      std::vector< double > energyGrid{ 1.0, -2.0, 3.0, 4.0, 5.0, 6.0 };
      njoy::ACEtk::Table::Slice grid = njoy::ACEtk::Table::slice( energyGrid );
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          tb.values( grid ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
  }
} // SCENARIO
