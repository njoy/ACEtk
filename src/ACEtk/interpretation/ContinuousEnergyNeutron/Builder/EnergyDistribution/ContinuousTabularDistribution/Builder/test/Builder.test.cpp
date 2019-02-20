#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::ContinuousTabularDistribution::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
    using CTBBuilder = decltype( 
        parentBuilder.continuousTabularDistribution() );

    struct TestBuilder : public CTBBuilder {
      using CTBBuilder::construct;
      using CTBBuilder::CTBBuilder;
    };

  TestBuilder cTB( parentBuilder );

  GIVEN( "valid inputs" ){
    std::vector< int > boundaries{ 0, 3 };
    std::vector< int > schemes{ 2, 1 };
    std::vector< double > energies{ 1.0, 2.0 };

    cTB.boundaries( njoy::utility::copy( boundaries ) )
       .schemes( njoy::utility::copy( schemes ) )
       .energies( njoy::utility::copy( energies ) );

    std::vector< int > INTT{ 1, 2 };
    std::vector< double > ene{ 1.0, 2.0};
    std::vector< double > pdf{ 0.25, 0.75 };
    std::vector< double > cdf{ 0.25, 1.0 };

    cTB.distributionData().interpolationParameter( INTT[ 0 ] )
                          .energies( njoy::utility::copy( ene ) )
                          .pdf( njoy::utility::copy( pdf ) )
                          .cdf( njoy::utility::copy( cdf ) )
        .add()
       .distributionData().interpolationParameter( INTT[ 1 ] )
                          .energies( njoy::utility::copy( ene ) )
                          .pdf( njoy::utility::copy( pdf ) )
                          .cdf( njoy::utility::copy( cdf ) )
        .add();

    auto distribution = cTB.construct();

    THEN( "the values can be verified" ){
      auto tab = distribution.tabulated;
      auto parameters = tab.parameters;
      CHECK( ranges::equal( boundaries, parameters->first ) );
      CHECK( ranges::equal( schemes, parameters->second ) );
      CHECK( ranges::equal( energies, tab.x ) );

      auto y = tab.y;
      CHECK( 2 == y.size() );

      int index = 0;
      {
        auto energyDistribution = y[ index ];
        CHECK( INTT[ index ] == energyDistribution.interpolationParameter );
        CHECK( ranges::equal( ene, energyDistribution.energies ) );
        CHECK( ranges::equal( pdf, energyDistribution.pdf ) );
        CHECK( ranges::equal( cdf, energyDistribution.cdf ) );
      }
      index = 1;
      {
        auto energyDistribution = y[ index ];
        CHECK( INTT[ index ] == energyDistribution.interpolationParameter );
        CHECK( ranges::equal( ene, energyDistribution.energies ) );
        CHECK( ranges::equal( pdf, energyDistribution.pdf ) );
        CHECK( ranges::equal( cdf, energyDistribution.cdf ) );
      }

    }
    
  } // GIVEN
  GIVEN( "invalid inputs" ){
    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          cTB.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          cTB.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
  }
} // SCENARIO
