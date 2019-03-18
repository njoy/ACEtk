#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Complete ContinuousEnergyNeutron::Builder" ){
  ContinuousEnergyNeutron::Builder nc{};

  GIVEN( "valid data" ){
    nc.header()
         .processDate( date::year{2019}/3/14 )
         .temperature( 2.5301E-8*dimwits::mega( electronVolts ) )
         .atomicWeightRatio( 233.024800 )
         .zaid( "92235.100nc" )
      .add(); // header

    std::vector< double > energyGrid{ 
      .0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    nc.energyGrid( njoy::utility::copy( energyGrid ) );

    std::vector< double > heating{ 
      0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };
    nc.heating( njoy::utility::copy( heating ) );

    { // nubar 
      std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
      std::vector< double > multiplicities{ 2.1, 2.2, 2.5, 2.5 };
      { // prompt
        nc.fissionMultiplicity( "prompt" )
          .tabulated()
            .energies( std::move( energies ) )
            .multiplicities( std::move( multiplicities ) )
          .add(); // prompt nubar

      }
    }
    { // MT=16
      std::vector< double > elasticXS{ 
        0.1, 1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1 };

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

      // Energy distribution
      std::vector< int > boundaries{ 0, 3 };
      std::vector< int > schemes{ 2, 1 };
      std::vector< double > energies{ 1.0, 2.0 };
      std::vector< double > probabilities{ 0.1, 0.2 };
      std::vector< int > INTT{ 1, 2 };
      std::vector< double > ene{ 1.0, 2.0};
      std::vector< double > pdf{ 0.25, 0.75 };
      std::vector< double > cdf{ 0.25, 1.0 };
      std::vector< double > R{ 0.99, 0.01 };
      std::vector< double > A{ 0.75, 0.22 };

      nc.reaction( 16 )
          .Q( -5.297781E5 )
          .energyGrid( nc.energyGrid() )
          .crossSection().values( elasticXS )
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
          .add() // angular distribution
          .energyDistribution()
            .boundaries( std::vector< int >{ 2 } )
            .schemes( std::vector< int >{ 2 } )
            .energies( std::vector< double >{5.320515E6, 2.0E7 } )
            .probabilities( njoy::utility::copy( probabilities ) )
            .kalbachMann()
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
               .add()    // distributionData
             .add() // kalbachMann
          .add()  // energyDistribution
        .add(); // reaction 16
    }


  } // GIVEN valid
  GIVEN( "invalid data" ){
  } // GIVEN invalid
} // SCENARIO complete

