#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

std::vector< double > energyGrid{ 4.0, 5.0, 6.0 };
njoy::ACEtk::Table::Slice grid{ energyGrid.begin(), energyGrid.end() };

template< typename B >
void addEnergyDistribution( B& builder ){
  std::vector< int > boundaries{ 0, 3 };
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

template< typename B >
void addAngularDistribution( B& builder ){
    std::vector< double > cosineBins{
      0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
      0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19,
      0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29,
      0.30, 0.31, 0.32
    };
    int f{1};
    std::vector< double > cosineGrid{ -0.1, 0.5, 0.8 };
    std::vector< double > pdf{ 0.1, 0.5, 0.4 };
    std::vector< double > cdf{ 0.1, 0.6, 1.0 };
    builder.angularDistribution().energyGrid( energyGrid )
                                 .isotropic()
                                 .tabulated().interpolationFlag( f )
                                             .cosineGrid( 
                                               njoy::utility::copy( 
                                                   cosineGrid ) )
                                             .pdf( njoy::utility::copy( 
                                                     pdf ) )
                                             .cdf( njoy::utility::copy( 
                                                     cdf ) )
                                   .add() 
                                 .equiprobableCosineBins().values( 
                                     njoy::utility::copy( cosineBins ) )
                                   .add()
      .add();
}

SCENARIO( "Testing ContinuousEnergyNeutron::Builder::Reaction::Builder" ){
    ContinuousEnergyNeutron::Builder parentBuilder{};
    using ReactionBuilder = decltype( parentBuilder.reaction( 14 ) );

    struct TestBuilder : public ReactionBuilder {
      using ReactionBuilder::constructNonNeutronProducing;
      using ReactionBuilder::constructNeutronProducing;
      using ReactionBuilder::ReactionBuilder;
    };

    TestBuilder tb{ parentBuilder, 14 };

  GIVEN( "valid values" ){
    double Q{ 3.14 };
    int neutronYield{ 2 };

    WHEN( "creating a Reaction::NeutronProducing" ){
      std::vector< double > XS{ 1.0, 2.0, 3.0 };
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

      tb.Q( Q );
      tb.crossSection().values( njoy::utility::copy( XS ) )
                       .energyGrid( grid )
                       .add();
      tb.neutronYield( neutronYield )
        .neutronYieldReferenceFrame(
          ContinuousEnergyNeutron::Builder::
            NeutronYieldReferenceFrame::CENTEROFMASS );
      addAngularDistribution( tb );
      addEnergyDistribution( tb );
      auto ppB = tb.photonProduction( 13 );
      ppB.crossSection().values( njoy::utility::copy( XS ) )
           .energyGrid( njoy::utility::copy( grid ) )
         .add() // crossSection
         .angularDistribution()
           .energyGrid( njoy::utility::copy( angularGrid ) )
           .cosineBins( 0,  njoy::utility::copy( bins[ 0 ] ) )
           .cosineBins( 1,  njoy::utility::copy( bins[ 1 ] ) )
           .cosineBins( 2,  njoy::utility::copy( bins[ 2 ] ) )
         .add(); // angularDistribution
      addEnergyDistribution( ppB );
      ppB.add(); // photonProduction

      auto reaction = tb.constructNeutronProducing();

      THEN( "the constructed Reaction can be verified" ){
        CHECK( Q == reaction.Q );
        CHECK( neutronYield == reaction.neutronYield );
        CHECK( ContinuousEnergyNeutron::Builder::NeutronYieldReferenceFrame::
                CENTEROFMASS == reaction.neutronYieldReferenceFrame );
        CHECK( XS == reaction.crossSection.values );
        CHECK( 14 == reaction.MT );
        CHECK( bool( reaction.photonProduction ) );
      }
    } // WHEN
    WHEN( "creating a Reaction with isotropic distribution" ){
      std::vector< double > XS{ 1.0, 2.0, 3.0 };

      tb.Q( Q );
      tb.crossSection().values( njoy::utility::copy( XS ) )
                       .energyGrid( grid )
                       .add();
      tb.neutronYield( neutronYield )
        .neutronYieldReferenceFrame(
            ContinuousEnergyNeutron::Builder::
              NeutronYieldReferenceFrame::LAB );
      tb.isotropic();
      addEnergyDistribution( tb );

      auto reaction = tb.constructNeutronProducing();

      THEN( "the constructed Reaction can be verified" ){
        CHECK( Q == reaction.Q );
        CHECK( neutronYield == reaction.neutronYield );
        CHECK( ContinuousEnergyNeutron::Builder::NeutronYieldReferenceFrame::
                LAB == reaction.neutronYieldReferenceFrame );
        CHECK( XS == reaction.crossSection.values );
        CHECK( 14 == reaction.MT );
      }
    } // WHEN
    WHEN( "valid neutron yield values are given" ){
      std::vector< int > validYields{
        -102, -101, -19, -4, -3, -2, -1, 1, 2, 3, 4, 19, 101, 102
      };
      for( auto yield : validYields ){
        THEN( "no exception is thrown when yield: " + std::to_string( yield ) ){
          CHECK_NOTHROW( tb.neutronYield( yield ));
        }
      }
    }
  } // GIVEN valid
  GIVEN( "invalid values" ){
    WHEN( "creating neutron producing reaction without an energy distribution" ){
      std::vector< double > energyGrid{ 
        0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
      std::vector< double > elasticXS{ 
        0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2 };

      // Angular distribution
      std::vector< double > grid{ 1.0, 2.0, 3.0, 4.0, 5.0 };
      std::vector< double > cosine{ -0.1, 0.5, 0.8 };
      std::vector< double > apdf{ 0.1, 0.5, 0.4 };
      std::vector< double > acdf{ 0.1, 0.6, 1.0 };
      std::vector< double > cosineBins{
        0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
        0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19,
        0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29,
        0.30, 0.31, 0.32
      };

      tb.Q( 0.0 )
        .crossSection()
          .values( njoy::utility::copy( elasticXS ) )
          .energyGrid( njoy::ACEtk::Table::slice( energyGrid ) )
        .add()  // crossSection
        .angularDistribution()
          .energyGrid( njoy::utility::copy( grid ) )
          .isotropic()
          .tabulated().interpolationFlag( 1 )
                      .cosineGrid( njoy::utility::copy( cosine ) )
                      .pdf( njoy::utility::copy( apdf ) )
                      .cdf( njoy::utility::copy( acdf ) )
          .add()  // tabulated
          .equiprobableCosineBins().values( 
              njoy::utility::copy( cosineBins ) )
          .add() // equiprobableCosineBins
          .isotropic()
          .isotropic()
        .add(); // angular distribution


      THEN( "an exception is thrown" ){
        CHECK_THROWS( tb.constructNeutronProducing() );
      }
    }
    WHEN( "adding secondary distributions to non neutron producing reaction" ){
      std::vector< int > nonProducingMTs{ 4, 101, 104 };
      THEN( "an exception is thrown" ){
        for( auto MT : nonProducingMTs ){
          TestBuilder tb{ parentBuilder, MT };
          CHECK_THROWS_AS( tb.angularDistribution(), std::range_error& );
          CHECK_THROWS_AS( tb.energyDistribution(), std::range_error& );
        }
      }
    }
    WHEN( "invalid neutron yield values are given" ){
      std::vector< int > invalidYields{ -100, -99, -21, -20, 20, 21, 99, 100 };
      for( auto yield : invalidYields ){
        THEN( "an exception is thrown when yield: " + std::to_string( yield ) ){
          CHECK_THROWS_AS( 
            tb.neutronYield ( yield ),
            details::verify::exceptions::InvalidNeutronYield& 
          );
        }
      }
    }
    WHEN( "cross section isn't all positive" ){
      std::vector< double > XS{ 1.0, -2.0, 3.0 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          tb.crossSection().values( njoy::utility::copy( XS ) )
                           .energyGrid( grid ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
  } // GIVEN invalid
} // SCENARIO
