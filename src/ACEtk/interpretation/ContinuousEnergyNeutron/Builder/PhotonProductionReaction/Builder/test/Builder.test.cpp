#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing PhotonProduction::Builder" ){
  ContinuousEnergyNeutron::Builder parentBuilder{};

  using PPBuilder = decltype( 
      parentBuilder.photonProductionReaction( 16, 102 ) );

  struct TestBuilder : public PPBuilder {
    using PPBuilder::construct;
    using PPBuilder::PPBuilder;
  };

  std::vector< double > angularGrid{ 1.0, 2.0, 3.0 };
  std::vector< std::array< double, 33 > > bins{
    { 0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
      0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19,
      0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29,
      0.30, 0.31, 0.32 },

        { 1.00, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09,
          1.10, 1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19,
          1.20, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29,
          1.30, 1.31, 1.32 },

        { 2.00, 2.01, 2.02, 2.03, 2.04, 2.05, 2.06, 2.07, 2.08, 2.09,
          2.10, 2.11, 2.12, 2.13, 2.14, 2.15, 2.16, 2.17, 2.18, 2.19,
          2.20, 2.21, 2.22, 2.23, 2.24, 2.25, 2.26, 2.27, 2.28, 2.29,
          2.30, 2.31, 2.32 }
  };
  WHEN( "constructing MF=12 (or 16) photon production reaction" ){
    int MF{ 12 };
    TestBuilder ppB{ parentBuilder, MF, 102 };

    std::vector< double > boundaries{ 0.0, 3.0 };
    std::vector< double > schemes{ 2.0, 1.0 };
    std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
    std::vector< double > values{ 2.1, 2.2, 2.5, 2.5 };

    WHEN( "adding a cross section" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( ppB.crossSection() );
      }
    }

    ppB.yields().boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .values( njoy::utility::copy( values ) )
        .add()
        .angularDistribution().energyGrid( njoy::utility::copy( angularGrid ) )
        .cosineBins( njoy::utility::copy( bins ) )
        .add();

    auto ppReaction = ppB.construct();
    THEN( "the values can be verified" ){
      auto angularDistribution = ppReaction.angularDistribution;
      CHECK( angularGrid == angularDistribution.energyGrid );
      CHECK( ranges::equal( bins, angularDistribution.cosineBins ) );

      auto yields = ppReaction.yields.value();
      CHECK( ranges::equal( boundaries, yields.boundaries ) );
      CHECK( ranges::equal( schemes, yields.schemes ) );
      CHECK( ranges::equal( energies, yields.x ) );
      CHECK( ranges::equal( values, yields.y ) );
    }
  }
  WHEN( "constructing MF=13 photon production reaction" ){
    int MF{ 13 };
    TestBuilder ppB{ parentBuilder, MF, 102 };

    std::vector< double > XS{ 1.0, 2.0, 3.0 };
    std::vector< double > energyGrid{ 4.0, 5.0, 6.0 };
    njoy::ACEtk::Table::Slice grid{ energyGrid.begin(), energyGrid.end() };

    WHEN( "adding yields" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS( ppB.yields() );
      }
    }

    ppB.crossSection().values( njoy::utility::copy( XS ) )
        .energyGrid( njoy::utility::copy( grid ) )
        .add()
        .angularDistribution().energyGrid( njoy::utility::copy( angularGrid ) )
        .cosineBins( njoy::utility::copy( bins ) )
        .add();

    auto ppReaction = ppB.construct();
    THEN( "the values can be verified" ){
      auto angularDistribution = ppReaction.angularDistribution;
      CHECK( angularGrid == angularDistribution.energyGrid );
      CHECK( ranges::equal( bins, angularDistribution.cosineBins ) );

      auto crossSection = ppReaction.crossSection.value();
      CHECK( ranges::equal( XS, crossSection.values ) );
      CHECK( ranges::equal( grid, crossSection.energyGrid ) );
    }
  }
} // SCENARIO