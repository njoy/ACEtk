#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::EnergyDependentWattSpectrum::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
    using EDWSBuilder = decltype( parentBuilder.energyDependentWattSpectrum() );

    struct TestBuilder : public EDWSBuilder {
      using EDWSBuilder::construct;
      using EDWSBuilder::EDWSBuilder;
    };

  TestBuilder eDWS( parentBuilder );

  GIVEN( "valid inputs" ){
    std::vector< int > aBoundaries{ 0, 3 };
    std::vector< int > bBoundaries{ 1, 4 };
    std::vector< int > aSchemes{ 2, 1 };
    std::vector< int > bSchemes{ 2, 3 };
    std::vector< double > aEnergies{ 1.0, 2.0, 3.0 };
    std::vector< double > bEnergies{ 1.1, 2.1, 3.1 };
    std::vector< double > a{ 0.1, 0.2, 0.3 };
    std::vector< double > b{ 1.1, 1.2, 1.3 };
    double restrictionEnergy{ 2.68 };

    eDWS.aTabulated()
           .boundaries( njoy::utility::copy( aBoundaries ) )
           .schemes( njoy::utility::copy( aSchemes ) )
           .energies( njoy::utility::copy( aEnergies ) )
           .values( njoy::utility::copy( a ) )
         .add()
        .bTabulated()
           .boundaries( njoy::utility::copy( bBoundaries ) )
           .schemes( njoy::utility::copy( bSchemes ) )
           .energies( njoy::utility::copy( bEnergies ) )
           .values( njoy::utility::copy( b ) )
         .add()
         .restrictionEnergy( restrictionEnergy );

    auto distribution = eDWS.construct();

    THEN( "the values can be verified " ){
      auto aTabulated = distribution.aTabulated;
      auto aParameters = aTabulated.parameters;
      CHECK( ranges::equal( aBoundaries, aParameters->first ) );
      CHECK( ranges::equal( aSchemes, aParameters->second ) );
      CHECK( ranges::equal( aEnergies, aTabulated.x ) );
      CHECK( ranges::equal( a, aTabulated.y ) );

      auto bTabulated = distribution.bTabulated;
      auto bParameters = bTabulated.parameters;
      CHECK( ranges::equal( bBoundaries, bParameters->first ) );
      CHECK( ranges::equal( bSchemes, bParameters->second ) );
      CHECK( ranges::equal( bEnergies, bTabulated.x ) );
      CHECK( ranges::equal( b, bTabulated.y ) );

      CHECK( restrictionEnergy == distribution.restrictionEnergy );

      AND_THEN( "the contents can be ACE-ified" ){
        std::vector< double > aceified{};
        aceified.push_back( aBoundaries.size() );
        aceified |= ranges::action::push_back( aBoundaries );
        aceified |= ranges::action::push_back( aSchemes );
        aceified.push_back( aEnergies.size() );
        aceified |= ranges::action::push_back( aEnergies );
        aceified |= ranges::action::push_back( a );
        aceified.push_back( bBoundaries.size() );
        aceified |= ranges::action::push_back( bBoundaries );
        aceified |= ranges::action::push_back( bSchemes );
        aceified.push_back( bEnergies.size() );
        aceified |= ranges::action::push_back( bEnergies );
        aceified |= ranges::action::push_back( b );
        aceified.push_back( restrictionEnergy );

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
          eDWS.aTabulated().energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          eDWS.aTabulated().energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
        CHECK_THROWS_AS( 
          eDWS.bTabulated().energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
    WHEN( "restriction energy is negative" ){
      THEN( "anexception is thrown" ){
        CHECK_THROWS_AS(
          eDWS.restrictionEnergy( -0.01 ),
          std::exception&
        );
      }
    }
  }
} // SCENARIO
