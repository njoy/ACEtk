#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "PhotonProduction components of ContinuousEnergyNeutron::Builder" ){
  ContinuousEnergyNeutron::Builder ncBuilder{};
  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
  std::vector< double > values{ 2.1, 2.2, 2.5, 2.5 };
  std::vector< double > probabilities{ 0.1, 0.2, 0.5, 0.2 };
  std::vector< double > ene{ 1.0, 2.0, 3.0};
  std::vector< int > INTT{ 1, 2 };
  std::vector< double > pdf{ 0.1, 0.5, 0.4 };
  std::vector< double > cdf{ 0.1, 0.6, 1.0 };

  std::vector< double > XS{ 1.0, 2.0, 3.0, 4.0 };
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
  std::vector< double > grid{ 1.0, 2.0, 3.0, 4.0 };
  ncBuilder.energyGrid( njoy::utility::copy( grid ) );

  WHEN( "valid MFS are used" ){
    {
      int MF = 12;
      CHECK_NOTHROW(
        ncBuilder.reaction( 102 )
          .photonProduction( MF )
                 .yields()
                    .boundaries ( njoy::utility::copy ( boundaries )  ) 
                    .schemes    ( njoy::utility::copy ( schemes    )  ) 
                    .energies   ( njoy::utility::copy ( energies   )  ) 
                    .values     ( njoy::utility::copy ( values     )  ) 
                 .add() // yields
                 .angularDistribution()
                    .energyGrid( njoy::utility::copy( angularGrid ) )
                    .cosineBins( 0, njoy::utility::copy( bins[ 0 ] ) )
                    .cosineBins( 1, njoy::utility::copy( bins[ 1 ] ) )
                    .cosineBins( 2, njoy::utility::copy( bins[ 2 ] ) )
                 .add() // angularDistribution
                 .energyDistribution()
                   .boundaries( njoy::utility::copy( boundaries ) )
                   .schemes( njoy::utility::copy( schemes ) )
                   .energies( njoy::utility::copy( energies ) )
                   .probabilities( njoy::utility::copy( probabilities ) )
                   .continuousTabularDistribution()
                     .boundaries( njoy::utility::copy( boundaries ) )
                     .schemes( njoy::utility::copy( schemes ) )
                     .energies( njoy::utility::copy( energies ) )
                     .distributionData()
                       .interpolationParameter( INTT[ 0 ] )
                       .energies( njoy::utility::copy( ene ) )
                       .pdf( njoy::utility::copy( pdf ) )
                       .cdf( njoy::utility::copy( cdf ) )
                       .add()
                     .distributionData()
                       .interpolationParameter( INTT[ 1 ] )
                       .energies( njoy::utility::copy( ene ) )
                       .pdf( njoy::utility::copy( pdf ) )
                       .cdf( njoy::utility::copy( cdf ) )
                     .add()
                     .distributionData()
                       .interpolationParameter( INTT[ 0 ] )
                       .energies( njoy::utility::copy( ene ) )
                       .pdf( njoy::utility::copy( pdf ) )
                       .cdf( njoy::utility::copy( cdf ) )
                     .add()
                     .distributionData()
                       .interpolationParameter( INTT[ 1 ] )
                       .energies( njoy::utility::copy( ene ) )
                       .pdf( njoy::utility::copy( pdf ) )
                       .cdf( njoy::utility::copy( cdf ) )
                     .add()
                   .add() // continuousTabularDistribution LAW=4
                 .add() // energy distribution
              .add()  // photonProduction
      );
    }
    {
      int MF = 13;
      CHECK_NOTHROW(
        ncBuilder.reaction( 103 )
          .photonProduction( MF )
                 .crossSection()
                    .values( njoy::utility::copy( XS ) )
                    .energyGrid( ncBuilder.energyGrid() )
                 .add()
                 .angularDistribution()
                    .energyGrid( njoy::utility::copy( angularGrid ) )
                    .cosineBins( 0, njoy::utility::copy( bins[ 0 ] ) )
                    .cosineBins( 1, njoy::utility::copy( bins[ 1 ] ) )
                    .cosineBins( 2, njoy::utility::copy( bins[ 2 ] ) )
                 .add()
                 .energyDistribution()
                   .boundaries( njoy::utility::copy( boundaries ) )
                   .schemes( njoy::utility::copy( schemes ) )
                   .energies( njoy::utility::copy( energies ) )
                   .probabilities( njoy::utility::copy( probabilities ) )
                   .continuousTabularDistribution()
                     .boundaries( njoy::utility::copy( boundaries ) )
                     .schemes( njoy::utility::copy( schemes ) )
                     .energies( njoy::utility::copy( energies ) )
                     .distributionData()
                       .interpolationParameter( INTT[ 0 ] )
                       .energies( njoy::utility::copy( ene ) )
                       .pdf( njoy::utility::copy( pdf ) )
                       .cdf( njoy::utility::copy( cdf ) )
                       .add()
                     .distributionData()
                       .interpolationParameter( INTT[ 1 ] )
                       .energies( njoy::utility::copy( ene ) )
                       .pdf( njoy::utility::copy( pdf ) )
                       .cdf( njoy::utility::copy( cdf ) )
                     .add()
                     .distributionData()
                       .interpolationParameter( INTT[ 0 ] )
                       .energies( njoy::utility::copy( ene ) )
                       .pdf( njoy::utility::copy( pdf ) )
                       .cdf( njoy::utility::copy( cdf ) )
                     .add()
                     .distributionData()
                       .interpolationParameter( INTT[ 1 ] )
                       .energies( njoy::utility::copy( ene ) )
                       .pdf( njoy::utility::copy( pdf ) )
                       .cdf( njoy::utility::copy( cdf ) )
                     .add()
                   .add() // continuousTabularDistribution LAW=4
                 .add() // energy distribution
                 .add()
      );
    }
    {
      int MF = 16;
      CHECK_NOTHROW(
        ncBuilder.reaction( 106 )
          .photonProduction( MF )
                 .yields()
                    .boundaries ( njoy::utility::copy ( boundaries )  ) 
                    .schemes    ( njoy::utility::copy ( schemes    )  ) 
                    .energies   ( njoy::utility::copy ( energies   )  ) 
                    .values     ( njoy::utility::copy ( values     )  ) 
                    .add()
                 .angularDistribution()
                    .energyGrid( njoy::utility::copy( angularGrid ) )
                    .cosineBins( 0, njoy::utility::copy( bins[ 0 ] ) )
                    .cosineBins( 1, njoy::utility::copy( bins[ 1 ] ) )
                    .cosineBins( 2, njoy::utility::copy( bins[ 2 ] ) )
                    .add()
                 .energyDistribution()
                   .boundaries( njoy::utility::copy( boundaries ) )
                   .schemes( njoy::utility::copy( schemes ) )
                   .energies( njoy::utility::copy( energies ) )
                   .probabilities( njoy::utility::copy( probabilities ) )
                   .continuousTabularDistribution()
                     .boundaries( njoy::utility::copy( boundaries ) )
                     .schemes( njoy::utility::copy( schemes ) )
                     .energies( njoy::utility::copy( energies ) )
                     .distributionData()
                       .interpolationParameter( INTT[ 0 ] )
                       .energies( njoy::utility::copy( ene ) )
                       .pdf( njoy::utility::copy( pdf ) )
                       .cdf( njoy::utility::copy( cdf ) )
                       .add()
                     .distributionData()
                       .interpolationParameter( INTT[ 1 ] )
                       .energies( njoy::utility::copy( ene ) )
                       .pdf( njoy::utility::copy( pdf ) )
                       .cdf( njoy::utility::copy( cdf ) )
                     .add()
                     .distributionData()
                       .interpolationParameter( INTT[ 0 ] )
                       .energies( njoy::utility::copy( ene ) )
                       .pdf( njoy::utility::copy( pdf ) )
                       .cdf( njoy::utility::copy( cdf ) )
                     .add()
                     .distributionData()
                       .interpolationParameter( INTT[ 1 ] )
                       .energies( njoy::utility::copy( ene ) )
                       .pdf( njoy::utility::copy( pdf ) )
                       .cdf( njoy::utility::copy( cdf ) )
                     .add()
                   .add() // continuousTabularDistribution LAW=4
                 .add() // energy distribution
                 .add()
      );
    }
  }
  WHEN( "invalid MFS are used" ){
    std::vector< int > invalidMFs{ 10, 11, 14, 15, 17, 18 };

    for( auto MF : invalidMFs ){
      THEN( "an exception is thrown when MF = " + std::to_string( MF ) ){
        CHECK_THROWS_AS(
          ncBuilder.reaction( 107 ).photonProduction( MF ),
          std::range_error&
        );
      }
    }
  }
  WHEN( "wrong sub-builder is called" ){
    THEN( "an exception is thrown" ){
      CHECK_THROWS_AS(
        ncBuilder.reaction( 108 ).photonProduction( 13 ).yields(),
        std::range_error&
      );

    }
    THEN( "an exception is thrown" ){
      CHECK_THROWS_AS(
        ncBuilder.reaction( 109 ).photonProduction( 12 ).crossSection(),
        std::range_error&
      );
      CHECK_THROWS_AS(
        ncBuilder.reaction( 110 ).photonProduction( 16 ).crossSection(),
        std::range_error&
      );
    }
  }
}
