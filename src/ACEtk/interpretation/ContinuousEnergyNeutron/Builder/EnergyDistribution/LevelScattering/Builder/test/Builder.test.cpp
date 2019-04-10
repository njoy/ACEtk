#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::LevelScattering::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
    using LSBuilder = decltype( parentBuilder.levelScattering() );

    struct TestBuilder : public LSBuilder {
      using LSBuilder::construct;
      using LSBuilder::LSBuilder;
    };

  TestBuilder lSBuilder( parentBuilder );

  GIVEN( "valid inputs" ){
    double awr{ 1.1 };
    double QValue{ 2.2 };
    lSBuilder.atomicWeightRatio( awr )
             .QValue( QValue );

    auto distribution = lSBuilder.construct();

    THEN( "the values of the distribution can be checked" ){
      CHECK( awr == distribution.atomicWeightRatio );
      CHECK( QValue == distribution.QValue );

      AND_THEN( "the contents can be ACE-ified" ){
        std::vector< double > aceified{};
        aceified.push_back( QValue );
        aceified.push_back( awr );

        Table::Data data{};
        distribution.ACEify( data, 0 );
        CHECK( ranges::equal( aceified, data.XSS() ) );
      }
    }
  } // GIVEN
  GIVEN( "invalid inputs" ){
    WHEN( "atomic weight ratio is negative" ){
      THEN( "anexception is thrown" ){
        CHECK_THROWS( lSBuilder.atomicWeightRatio( -1.0 ) );
      }
    }
  } // GIVEN
} // SCENARIO
