#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;


template< typename B >
void LAW1( B& ED ){
  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
  std::vector< double > eout_v{ 1.1, 1.2, 1.3 };
  std::array< double, 3 > eout_a{ 1.1, 1.2, 1.4 };

  ED.tabularEquiprobableEnergyBins()
      .boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) )
      .outgoingEnergyTable( njoy::utility::copy( eout_v ) )
      .outgoingEnergyTable( njoy::utility::copy( eout_a ) )
      .outgoingEnergyTable( njoy::utility::copy( eout_a ) )
      .outgoingEnergyTable( njoy::utility::copy( eout_a ) )
      .add(); // tabularEquiprobableEnergyBins
}

template< typename B >
void LAW2( B& ED ){
  ED.discretePhotonEnergy()
      .energy( 3.14 )
      .primaryFlag( 1 )
      .add(); // discretePhotonEnergy
}

template< typename B >
void LAW3( B& ED ){
  ED.levelScattering()
      .atomicWeightRatio( 235.98 )
      .QValue( 2.765 )
      .add(); // levelScattering
}

template< typename B >
void LAW4( B& ED ){
  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0 };

  std::vector< int > INTT{ 1, 2 };
  std::vector< double > ene{ 1.0, 2.0};
  std::vector< double > pdf{ 0.25, 0.75 };
  std::vector< double > cdf{ 0.25, 1.0 };

  ED.continuousTabularDistribution()
      .boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) )
      .distributionData()
        .interpolationParameter( INTT[ 0 ] )
        .energies( njoy::utility::copy( ene ) )
        .pdf( njoy::utility::copy( pdf ) )
        .cdf( njoy::utility::copy( cdf ) )
      .add() // distributionData
      .distributionData()
        .interpolationParameter( INTT[ 1 ] )
        .energies( njoy::utility::copy( ene ) )
        .pdf( njoy::utility::copy( pdf ) )
        .cdf( njoy::utility::copy( cdf ) )
      .add() // distributionData
    .add(); // continuousTabularDistribution
}

template< typename B >
void LAW5( B& ED ){
  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0 };
  std::vector< double > theta{ 2.5, 3.7 };
  std::vector< double > X{ 1.0, 2.2, 5.4 };

  ED.generalEvaporationSpectrum()
      .boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) )
      .effectiveTemperature( njoy::utility::copy( theta ) )
      .equiprobableBins( njoy::utility::copy( X ) )
    .add(); // generalEvaporationSpectrum
}

template< typename B >
void LAW7( B& ED ){

  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0 };
  std::vector< double > theta{ 2.5, 3.7 };
  double U{ 3.14 };

  ED.simpleMaxwellianFissionSpectrum()
      .boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) )
      .effectiveTemperature( njoy::utility::copy( theta ) )
      .restrictionEnergy( U )
    .add(); // simpleMaxwellianFissionSpectrum

}

template< typename B >
void LAW9( B& ED ){
  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0 };
  std::vector< double > theta{ 2.5, 3.7 };
  double U{ 3.14 };

  ED.evaporationSpectrum()
      .boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) )
      .effectiveTemperature( njoy::utility::copy( theta ) )
      .restrictionEnergy( U )
    .add(); // evaporationSpectrum
}

template< typename B >
void LAW11( B& ED ){
  std::vector< int > aBoundaries{ 0, 3 };
  std::vector< int > bBoundaries{ 1, 4 };
  std::vector< int > aSchemes{ 2, 1 };
  std::vector< int > bSchemes{ 2, 3 };
  std::vector< double > aEnergies{ 1.0, 2.0, 3.0 };
  std::vector< double > bEnergies{ 1.1, 2.1, 3.1 };
  std::vector< double > a{ 0.1, 0.2, 0.3 };
  std::vector< double > b{ 1.1, 1.2, 1.3 };
  double restrictionEnergy{ 2.68 };

  ED.energyDependentWattSpectrum()
      .aTabulated()
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
        .restrictionEnergy( restrictionEnergy )
    .add(); // energyDependentWattSpectrum
}

template< typename B >
void LAW22( B& ED ){
  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0 };
  std::vector< double > P{ 0.1, 0.2, 0.4 };
  std::vector< double > T{ 1.1, 1.2, 1.4 };
  std::vector< double > C{ 2.1, 2.2, 2.4 };

  ED.tabularLinearFunctions()
      .boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) )
      .distributionData()
         .P( njoy::utility::copy( P ) )
         .T( njoy::utility::copy( T ) )
         .C( njoy::utility::copy( C ) )
      .add() // distributionData
      .distributionData()
         .P( njoy::utility::copy( P ) )
         .T( njoy::utility::copy( T ) )
         .C( njoy::utility::copy( C ) )
      .add() // distributionData
    .add(); // tabularLinearFunctions
}

template< typename B >
void LAW44( B& ED ){
  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0 };
  std::vector< int > INTT{ 1, 2 };
  std::vector< double > ene{ 1.0, 2.0};
  std::vector< double > pdf{ 0.25, 0.75 };
  std::vector< double > cdf{ 0.25, 1.0 };
  std::vector< double > R{ 0.99, 0.01 };
  std::vector< double > A{ 0.75, 0.22 };

  ED.kalbachMann()
      .boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) )
      .distributionData()
        .interpolationParameter( INTT[ 0 ] )
        .energies( njoy::utility::copy( ene ) )
        .pdf( njoy::utility::copy( pdf ) )
        .cdf( njoy::utility::copy( cdf ) )
        .precompoundFraction( njoy::utility::copy( R ) )
        .angularDistributionSlope( njoy::utility::copy( A ) )
      .add() // distributionData
      .distributionData()
        .interpolationParameter( INTT[ 1 ] )
        .energies( njoy::utility::copy( ene ) )
        .pdf( njoy::utility::copy( pdf ) )
        .cdf( njoy::utility::copy( cdf ) )
        .precompoundFraction( njoy::utility::copy( R ) )
        .angularDistributionSlope( njoy::utility::copy( A ) )
      .add()   // distributionData
    .add(); // kalbachMann
}

SCENARIO( "Testing EnergyDistribtion::Builder" ){
  ContinuousEnergyNeutron::Builder CENBuilder;
  using ParentBuilder = decltype( CENBuilder.reaction( 14 ) );

  ParentBuilder parentBuilder{ CENBuilder, 14 };
  using EDBuilder = decltype( parentBuilder.energyDistribution() );

  struct TestBuilder : public EDBuilder {
    using EDBuilder::construct;
    using EDBuilder::EDBuilder;
  };

  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
  std::vector< double > probabilities{ 0.1, 0.2, 0.5, 0.2 };

  GIVEN( "valid inputs" ){
    TestBuilder tb{ parentBuilder };

    tb.boundaries( njoy::utility::copy( boundaries ) )
      .schemes( njoy::utility::copy( schemes ) )
      .energies( njoy::utility::copy( energies ) )
      .probabilities( njoy::utility::copy( probabilities ) );

    std::vector< int > LAWS{ 1, 2, 3, 4, 5, 7, 9, 11, 22, /*24,*/ 44, /*61, 66, 67 */ };

    for( auto LAW : LAWS ){
      THEN( "LAW=" + std::to_string( LAW ) + " can be given" ){
        njoy::Log::info( "Trying LAW={}", LAW );

        switch( LAW ){
          case 1:  LAW1( tb ); break;
          case 2:  LAW2( tb ); break;
          case 3:  LAW3( tb ); break;
          case 4:  LAW4( tb ); break;
          case 5:  LAW5( tb ); break;
          case 7:  LAW7( tb ); break;
          case 9:  LAW9( tb ); break;
          case 11: LAW11( tb ); break;
          case 22: LAW22( tb ); break;
          case 44: LAW44( tb ); break;
          default:
            njoy::Log::info( "I don't know what to do with LAW={}", LAW );
        }

        CHECK_NOTHROW( tb.construct() );

      } // THEN a law can be given
    } // for LAW
  } // GIVEN
  GIVEN( "invalid inputs" ){
    TestBuilder tb{ parentBuilder };

    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
    WHEN( "probabilities are negative" ){
      std::vector< double > probabilities{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tb.probabilities( njoy::utility::copy( probabilities ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
  }
} // SCENARIO
