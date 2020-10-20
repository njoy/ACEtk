#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

template< typename B >
void addEnergyDistribution( B& builder ){
  std::vector< int > boundaries{ 1, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
  std::vector< double > probabilities{ 0.1, 0.2, 0.5, 0.2 };

  std::vector< int > LAWS{ 1, 2, 3, 4, 5, 7, 9, 11 };
  for( auto LAW : LAWS ){
    auto ED = builder.energyDistribution();
    ED.boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) )
      .probabilities( njoy::utility::copy( probabilities ) )
      .levelScattering()
        .atomicWeightRatio( 235.98 )
        .QValue( 2.765 )
      .add(); // levelScattering
    ED.add();
  }
}

SCENARIO( "Testing PhotonProduction::Builder" ){
  ContinuousEnergyNeutron::Builder parentBuilder{};

  auto reacBuilder = parentBuilder.reaction( 16 );
  using PPBuilder = decltype( reacBuilder.photonProduction( 12 ) );

  struct TestBuilder : public PPBuilder {
    using PPBuilder::construct;
    using PPBuilder::PPBuilder;
  };

  std::vector< double > angularGrid{ 1.0, 2.0, 3.0 };
  std::vector< std::array< double, 33 > > bins{
    {{ 0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
      0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19,
      0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29,
      0.30, 0.31, 0.32 }},

    {{ 0.100, 0.101, 0.102, 0.103, 0.104, 0.105, 0.106, 0.107, 0.108, 0.109,
      0.110, 0.111, 0.112, 0.113, 0.114, 0.115, 0.116, 0.117, 0.118, 0.119,
      0.120, 0.121, 0.122, 0.123, 0.124, 0.125, 0.126, 0.127, 0.128, 0.129,
      0.130, 0.131, 0.132 }},

    {{ 0.200, 0.201, 0.202, 0.203, 0.204, 0.205, 0.206, 0.207, 0.208, 0.209,
      0.210, 0.211, 0.212, 0.213, 0.214, 0.215, 0.216, 0.217, 0.218, 0.219,
      0.220, 0.221, 0.222, 0.223, 0.224, 0.225, 0.226, 0.227, 0.228, 0.229,
      0.230, 0.231, 0.232 }}
  };
  WHEN( "constructing MF=12 (or 16) photon production reaction" ){
    int MF{ 12 };
    TestBuilder ppB{ reacBuilder, MF, 102 };

    std::vector< int > boundaries{ 1, 3 };
    std::vector< int > schemes{ 2, 1 };
    std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
    std::vector< double > values{ 2.1, 2.2, 2.5, 2.5 };

    WHEN( "adding a cross section" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( ppB.crossSection(), std::range_error& );
      }
    }

    ppB.yields().boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .values( njoy::utility::copy( values ) )
        .add()
        .angularDistribution()
          .energyGrid( njoy::utility::copy( angularGrid ) )
          .cosineBins( 0, njoy::utility::copy( bins[ 0 ] ) )
          .cosineBins( 1, njoy::utility::copy( bins[ 1 ] ) )
          .cosineBins( 2, njoy::utility::copy( bins[ 2 ] ) )
        .add();
    addEnergyDistribution( ppB );

    auto ppReaction = ppB.construct();
    THEN( "the values can be verified" ){
      auto angularDistribution = ppReaction.angularDistribution;
      CHECK( angularGrid == angularDistribution.energyGrid );
      CHECK( ranges::equal( bins[ 0 ], angularDistribution.cosineBins[ 0 ].value() ) );
      CHECK( ranges::equal( bins[ 1 ], angularDistribution.cosineBins[ 1 ].value() ) );
      CHECK( ranges::equal( bins[ 2 ], angularDistribution.cosineBins[ 2 ].value() ) );

      auto& yields = std::get< 1 >( ppReaction.crossSection );
      auto& parameters = yields.tabulated.parameters.value();
      CHECK( ranges::equal( boundaries, parameters.first ) );
      CHECK( ranges::equal( schemes, parameters.second ) );
      CHECK( ranges::equal( energies, yields.tabulated.x ) );
      CHECK( ranges::equal( values, yields.tabulated.y ) );
    }
  }
  WHEN( "constructing MF=13 photon production reaction" ){
    int MF{ 13 };
    TestBuilder ppB{ reacBuilder, MF, 102 };

    std::vector< double > XS{ 1.0, 2.0, 3.0 };
    std::vector< double > energyGrid{ 4.0, 5.0, 6.0 };
    njoy::ACEtk::Table::Slice grid{ energyGrid.begin(), energyGrid.end() };

    WHEN( "adding yields" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( ppB.yields(), std::range_error& );
      }
    }

    ppB.crossSection().values( njoy::utility::copy( XS ) )
        .energyGrid( njoy::utility::copy( grid ) )
        .add()
        .angularDistribution()
          .energyGrid( njoy::utility::copy( angularGrid ) )
          .cosineBins( 0, njoy::utility::copy( bins[ 0 ] ) )
          .cosineBins( 1, njoy::utility::copy( bins[ 1 ] ) )
          .cosineBins( 2, njoy::utility::copy( bins[ 2 ] ) )
        .add();
    addEnergyDistribution( ppB );

    auto ppReaction = ppB.construct();
    THEN( "the values can be verified" ){
      auto angularDistribution = ppReaction.angularDistribution;
      CHECK( angularGrid == angularDistribution.energyGrid );
      CHECK( ranges::equal( bins[ 0 ], angularDistribution.cosineBins[ 0 ].value() ) );
      CHECK( ranges::equal( bins[ 1 ], angularDistribution.cosineBins[ 1 ].value() ) );
      CHECK( ranges::equal( bins[ 2 ], angularDistribution.cosineBins[ 2 ].value() ) );

      auto& crossSection = std::get< 0 >( ppReaction.crossSection );
      CHECK( ranges::equal( XS, crossSection.data.values ) );
      CHECK( ranges::equal( grid, crossSection.data.energyGrid ) );
    }
  }
} // SCENARIO
