#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "PhotonProductionReaction components of ContinuousEnergyNeutron::Builder" ){
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
  std::vector< double > grid{ 1.0, 2.0, 3.0, 4.0 };
  ncBuilder.energyGrid( njoy::utility::copy( grid ) );

  WHEN( "valid MFS are used" ){
    {
      int MF = 12;
      CHECK_NOTHROW(
        ncBuilder.photonProductionReaction( MF, 102 )
                 .yields()
                    .boundaries ( njoy::utility::copy ( boundaries )  ) 
                    .schemes    ( njoy::utility::copy ( schemes    )  ) 
                    .energies   ( njoy::utility::copy ( energies   )  ) 
                    .values     ( njoy::utility::copy ( values     )  ) 
                 .add() // yields
                 .angularDistribution()
                    .energyGrid( njoy::utility::copy( angularGrid ) )
                    .cosineBins( njoy::utility::copy( bins ) )
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
              .add()  // photonProductionReaction
      );
    }
    {
      int MF = 13;
      CHECK_NOTHROW(
        ncBuilder.photonProductionReaction( MF, 103 )
                 .crossSection()
                    .values( njoy::utility::copy( XS ) )
                    .energyGrid( ncBuilder.energyGrid() )
                    .add()
                 .angularDistribution()
                    .energyGrid( njoy::utility::copy( angularGrid ) )
                    .cosineBins( njoy::utility::copy( bins ) )
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
        ncBuilder.photonProductionReaction( MF, 106 )
                 .yields()
                    .boundaries ( njoy::utility::copy ( boundaries )  ) 
                    .schemes    ( njoy::utility::copy ( schemes    )  ) 
                    .energies   ( njoy::utility::copy ( energies   )  ) 
                    .values     ( njoy::utility::copy ( values     )  ) 
                    .add()
                 .angularDistribution()
                    .energyGrid( njoy::utility::copy( angularGrid ) )
                    .cosineBins( njoy::utility::copy( bins ) )
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
          ncBuilder.photonProductionReaction( MF, 107 ),
          std::range_error&
        );
      }
    }
  }
  WHEN( "wrong sub-builder is called" ){
    THEN( "an exception is thrown" ){
      CHECK_THROWS_AS(
        ncBuilder.photonProductionReaction( 13, 108 ).yields(),
        std::range_error&
      );

    }
    THEN( "an exception is thrown" ){
      CHECK_THROWS_AS(
        ncBuilder.photonProductionReaction( 12, 109 ).crossSection(),
        std::range_error&
      );
      CHECK_THROWS_AS(
        ncBuilder.photonProductionReaction( 16, 110 ).crossSection(),
        std::range_error&
      );
    }
  }
}
