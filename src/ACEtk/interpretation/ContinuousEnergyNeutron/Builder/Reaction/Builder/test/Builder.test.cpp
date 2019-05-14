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

        {{ 1.00, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09,
          1.10, 1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19,
          1.20, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29,
          1.30, 1.31, 1.32 }},

        {{ 2.00, 2.01, 2.02, 2.03, 2.04, 2.05, 2.06, 2.07, 2.08, 2.09,
          2.10, 2.11, 2.12, 2.13, 2.14, 2.15, 2.16, 2.17, 2.18, 2.19,
          2.20, 2.21, 2.22, 2.23, 2.24, 2.25, 2.26, 2.27, 2.28, 2.29,
          2.30, 2.31, 2.32 }}
      };

      tb.Q( Q );
      tb.crossSection().values( njoy::utility::copy( XS ) )
                       .energyGrid( grid )
                       .add();
      tb.neutronYield( neutronYield, 
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
           .cosineBins( njoy::utility::copy( bins ) )
         .add(); // angularDistribution
      addEnergyDistribution( ppB );
      ppB.add(); // photonProduction

      auto reaction = tb.constructNeutronProducing();

      THEN( "the constructed Reaction can be verified" ){
        CHECK( Q == reaction.Q );
        CHECK( -1*neutronYield == reaction.neutronYield );
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
      tb.neutronYield( neutronYield, 
                       ContinuousEnergyNeutron::Builder::
                          NeutronYieldReferenceFrame::CENTEROFMASS );
      tb.isotropic();
      addEnergyDistribution( tb );

      auto reaction = tb.constructNeutronProducing();

      THEN( "the constructed Reaction can be verified" ){
        CHECK( Q == reaction.Q );
        CHECK( -1*neutronYield == reaction.neutronYield );
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
          CHECK_NOTHROW( 
            tb.neutronYield( yield, 
                             ContinuousEnergyNeutron::Builder::
                                NeutronYieldReferenceFrame::LAB ) );
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
            tb.neutronYield ( yield, 
                             ContinuousEnergyNeutron::Builder::
                                NeutronYieldReferenceFrame::LAB ),
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
    WHEN( "neutron yield isn't correct" ){
      THEN( "an exception is thrown" ){
        CHECK_THROWS(
          tb.neutronYield( 0, 
                          ContinuousEnergyNeutron::Builder::
                              NeutronYieldReferenceFrame::CENTEROFMASS )
        );
      }

    }
  } // GIVEN invalid
} // SCENARIO
