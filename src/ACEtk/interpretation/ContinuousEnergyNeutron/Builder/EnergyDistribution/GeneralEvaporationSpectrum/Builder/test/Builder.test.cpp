#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::GeneralEvaporationSpectrum::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
    using GESBuilder = decltype( parentBuilder.generalEvaporationSpectrum() );

    struct TestBuilder : public GESBuilder {
      using GESBuilder::construct;
      using GESBuilder::GESBuilder;
    };

  TestBuilder gES( parentBuilder );

  GIVEN( "valid inputs" ){
    std::vector< int > boundaries{ 1, 3 };
    std::vector< int > schemes{ 2, 1 };
    std::vector< double > energies{ 1.0, 2.0 };
    std::vector< double > theta{ 2.5, 3.7 };
    std::vector< double > X{ 1.0, 2.2, 5.4 };

    gES.boundaries( njoy::utility::copy( boundaries ) )
       .schemes( njoy::utility::copy( schemes ) )
       .energies( njoy::utility::copy( energies ) )
       .effectiveTemperature( njoy::utility::copy( theta ) )
       .equiprobableBins( njoy::utility::copy( X ) );

    auto distribution = gES.construct();
    THEN( "the values can be verified" ){
      auto tab = distribution.tabulatedEffectiveTemperature;
      auto parameters = tab.parameters;
      CHECK( ranges::equal( boundaries, parameters->first ) );
      CHECK( ranges::equal( schemes, parameters->second ) );
      CHECK( ranges::equal( energies, tab.x ) );
      CHECK( ranges::equal( theta, tab.y ) );
      CHECK( ranges::equal( X, distribution.equiprobableBins ) );

      AND_THEN( "the contents can be ACE-ified" ){
        std::vector< double > aceified{};
        aceified.push_back( boundaries.size() );
        aceified |= ranges::action::push_back( boundaries );
        aceified |= ranges::action::push_back( schemes );
        aceified.push_back( energies.size() );
        aceified |= ranges::action::push_back( energies );
        aceified |= ranges::action::push_back( theta );
        aceified.push_back( X.size() );
        aceified |= ranges::action::push_back( X );

        Table::Data data{};
        distribution.ACEify( data, 0 );

        CHECK( ranges::equal( aceified, data.XSS() ) );
      }
    }
  } // GIVEN valid
  GIVEN( "invalid inputs" ){
    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          gES.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          gES.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
    WHEN( "effective temperatures are negative" ){
      std::vector< double > theta{ 1.0, 2.0, -5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          gES.effectiveTemperature( njoy::utility::copy( theta ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "equiprobable bins are negative" ){
      std::vector< double > X{ 1.0, 2.0, -5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          gES.equiprobableBins( njoy::utility::copy( X ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
  } // GIVEN invalid
} // SCENARIO
