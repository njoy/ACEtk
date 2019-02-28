#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::LaboratoryAngleEnergy::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
    using LAEBuilder = decltype( parentBuilder.laboratoryAngleEnergy() );

    struct TestBuilder : public LAEBuilder {
      using LAEBuilder::construct;
      using LAEBuilder::LAEBuilder;
    };

  TestBuilder lAE( parentBuilder );

  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0 };

  std::vector< double > cosines{ -0.99, 0.01, 0.75 };
  std::vector< int > INTMUs{ 1, 2 };

  std::vector< double > ene{ 1.0, 2.0};
  std::vector< double > pdf{ 0.25, 0.75 };
  std::vector< double > cdf{ 0.25, 1.0 };
  std::vector< int > INTEPs{ 1, 2 };

  GIVEN( "valid inputs" ){
    lAE.boundaries( njoy::utility::copy( boundaries ) )
       .schemes( njoy::utility::copy( schemes ) )
       .energies( njoy::utility::copy( energies ) )
       .angularDistribution()
         .interpolationParameter( INTMUs[ 0 ] )
         .cosines( njoy::utility::copy( cosines ) )
         .energyDistribution()
           .interpolationParameter( INTEPs[ 0 ] )
           .energies( njoy::utility::copy( ene ) )
           .pdf( njoy::utility::copy( pdf ) )
           .cdf( njoy::utility::copy( cdf ) )
         .add() // energyDistribution
         .energyDistribution()
           .interpolationParameter( INTEPs[ 1 ] )
           .energies( njoy::utility::copy( ene ) )
           .pdf( njoy::utility::copy( pdf ) )
           .cdf( njoy::utility::copy( cdf ) )
         .add() // energyDistribution
         .energyDistribution()
           .interpolationParameter( INTEPs[ 0 ] )
           .energies( njoy::utility::copy( ene ) )
           .pdf( njoy::utility::copy( pdf ) )
           .cdf( njoy::utility::copy( cdf ) )
         .add()  // energyDistribution
       .add() // angularDistribution
       .angularDistribution()
         .interpolationParameter( INTMUs[ 1 ] )
         .cosines( njoy::utility::copy( cosines ) )
         .energyDistribution()
           .interpolationParameter( INTEPs[ 0 ] )
           .energies( njoy::utility::copy( ene ) )
           .pdf( njoy::utility::copy( pdf ) )
           .cdf( njoy::utility::copy( cdf ) )
         .add() // energyDistribution
         .energyDistribution()
           .interpolationParameter( INTEPs[ 1 ] )
           .energies( njoy::utility::copy( ene ) )
           .pdf( njoy::utility::copy( pdf ) )
           .cdf( njoy::utility::copy( cdf ) )
         .add() // energyDistribution
         .energyDistribution()
           .interpolationParameter( INTEPs[ 0 ] )
           .energies( njoy::utility::copy( ene ) )
           .pdf( njoy::utility::copy( pdf ) )
           .cdf( njoy::utility::copy( cdf ) )
         .add()  // energyDistribution
       .add(); // angularDistribution

    auto distribution = lAE.construct();
    THEN( "the values can be verified" ){
      auto tab = distribution.tabulated;
      auto parameters = tab.parameters;
      CHECK( ranges::equal( boundaries, parameters->first ) );
      CHECK( ranges::equal( schemes, parameters->second ) );
      CHECK( ranges::equal( energies, tab.x ) );

      auto y = tab.y;
      CHECK( 2 == y.size() );
    }
  } // GIVEN valid
  GIVEN( "invalid inputs" ){
    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          lAE.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          lAE.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
    WHEN( "wrong number of distributionData members" ){
      lAE.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .angularDistribution()
          .interpolationParameter( INTMUs[ 0 ] )
          .cosines( njoy::utility::copy( cosines ) )
          .energyDistribution()
            .interpolationParameter( INTEPs[ 0 ] )
            .energies( njoy::utility::copy( ene ) )
            .pdf( njoy::utility::copy( pdf ) )
            .cdf( njoy::utility::copy( cdf ) )
          .add() // energyDistribution
          .energyDistribution()
            .interpolationParameter( INTEPs[ 1 ] )
            .energies( njoy::utility::copy( ene ) )
            .pdf( njoy::utility::copy( pdf ) )
            .cdf( njoy::utility::copy( cdf ) )
          .add() // energyDistribution
          .energyDistribution()
            .interpolationParameter( INTEPs[ 0 ] )
            .energies( njoy::utility::copy( ene ) )
            .pdf( njoy::utility::copy( pdf ) )
            .cdf( njoy::utility::copy( cdf ) )
          .add()  // energyDistribution
        .add(); // angularDistribution

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          lAE.construct(),
          std::range_error&
        );
      }
    }
  }
} // SCENARIO
