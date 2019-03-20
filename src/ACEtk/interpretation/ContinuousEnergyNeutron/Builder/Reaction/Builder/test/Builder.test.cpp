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
    struct ParentBuilder: public ContinuousEnergyNeutron::Builder{
      using ContinuousEnergyNeutron::Builder::reactions_;
    };
    ParentBuilder parentBuilder{};
    using ReactionBuilder = decltype( parentBuilder.reaction( 14 ) );

    struct TestBuilder : public ReactionBuilder {
      using ReactionBuilder::construct;
      using ReactionBuilder::ReactionBuilder;
    };

    TestBuilder tb{ parentBuilder, 14 };

  GIVEN( "valid values" ){
    double Q{ 3.14 };
    int neutronYield{ 2 };

    WHEN( "creating a Reaction Builder without a parent energyGrid" ){
      std::vector< double > XS{ 1.0, 2.0, 3.0 };

      tb.Q( Q );
      tb.crossSection().values( njoy::utility::copy( XS ) )
                       .energyGrid( grid )
                       .add();
      tb.neutronYield( neutronYield, 
                       ContinuousEnergyNeutron::Builder::
                          NeutronYieldReferenceFrame::CENTEROFMASS );
      addAngularDistribution( tb );
      addEnergyDistribution( tb );
      tb.add();

      THEN( "the constructed Reaction can be verified" ){
        auto reaction = parentBuilder.reactions_[ 14 ];
        CHECK( Q == reaction.Q );
        CHECK( -1*neutronYield == reaction.neutronYield );
        CHECK( XS == reaction.crossSection.values );
        CHECK( 14 == reaction.MT );

        CHECK( 1 == 
               static_cast< ParentBuilder& >(parentBuilder).reactions_.size() );
      }
    } // WHEN
    WHEN( "all the pieces of a Reaction are not present" ){
      CHECK_THROWS( tb.construct() );
    }
    WHEN( "valid neutron yield values are given" ){
      std::vector< int > validYields{
        -102, -101, -19, -4, -3, -2, -1, 0, 1, 2, 3, 4, 19, 101, 102
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
  } // GIVEN invalid
} // SCENARIO
