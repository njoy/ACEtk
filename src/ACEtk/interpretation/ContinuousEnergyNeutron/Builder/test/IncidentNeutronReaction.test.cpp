#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "incident neutron reaction" ){
  ContinuousEnergyNeutron::Builder ncBuilder{};
  std::vector< double > grid{ 1.0, 2.0, 3.0, 4.0, 5.0 };
  ncBuilder.energyGrid( njoy::utility::copy( grid ) );

  GIVEN( "data for a reaction" ){
    std::vector< double > XS{ 1.1, 2.1, 3.1 };
    std::vector< double > grid{1.0, 2.0, 3.0};
    double Qvalue{ 1.23 };
    ncBuilder.energyGrid( njoy::utility::copy( grid ) );

    int neutronYield{ 2 };
    std::vector< double > cosineBins{
      0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
      0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19,
      0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29,
      0.30, 0.31, 0.32
    };
    int f{1};
    std::vector< double > cosine{ -0.1, 0.5, 0.8 };
    std::vector< double > pdf{ 0.1, 0.5, 0.4 };
    std::vector< double > cdf{ 0.1, 0.6, 1.0 };

    std::vector< int > boundaries{ 0, 3 };
    std::vector< int > schemes{ 2, 1 };
    std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
    std::vector< double > probabilities{ 0.1, 0.2, 0.5, 0.2 };
    std::vector< double > ene{ 1.0, 2.0, 3.0};
    std::vector< int > INTT{ 1, 2 };

    int MT{ 14 };
    WHEN( "adding a reaction" ){
      THEN( "no exception is thrown" ){
        CHECK_NOTHROW( 
          ncBuilder.reaction( MT )
                      .Q( Qvalue )
                      .crossSection()
                        .values( njoy::utility::copy( XS ) )
                        .energyGrid( ncBuilder.energyGrid() )
                      .add() // crossSection
                      .neutronYield( neutronYield, 
                                ContinuousEnergyNeutron::Builder::
                                    NeutronYieldReferenceFrame::CENTEROFMASS )
                      .angularDistribution()
                        .energyGrid( grid )
                        .isotropic()
                        .tabulated().interpolationFlag( f )
                                    .cosineGrid( njoy::utility::copy( cosine ) )
                                    .pdf( njoy::utility::copy( pdf ) )
                                    .cdf( njoy::utility::copy( cdf ) )
                          .add() 
                        .equiprobableCosineBins().values( 
                            njoy::utility::copy( cosineBins ) )
                          .add()
                      .add() // angular distribution
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
                    .add() // reaction
        );
      }
    } // WHEN
    WHEN( "adding a duplicate reaction" ){
      THEN( "an exception is thrown" ){
        ncBuilder.reaction( MT )
                  .crossSection()
                    .values( njoy::utility::copy( XS ) )
                    .energyGrid( ncBuilder.energyGrid() )
                  .add() // crossSection
                  .neutronYield( neutronYield, 
                            ContinuousEnergyNeutron::Builder::
                                NeutronYieldReferenceFrame::CENTEROFMASS )
                  .Q( Qvalue )
                  .angularDistribution()
                    .energyGrid( grid )
                    .isotropic()
                    .tabulated().interpolationFlag( f )
                                .cosineGrid( njoy::utility::copy( cosine ) )
                                .pdf( njoy::utility::copy( pdf ) )
                                .cdf( njoy::utility::copy( cdf ) )
                      .add() 
                    .equiprobableCosineBins().values( 
                        njoy::utility::copy( cosineBins ) )
                      .add()
                  .add() // angular distribution
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
                 .add(); // reaction
        CHECK_THROWS(
          ncBuilder.reaction( MT )
                   .crossSection()
                    .values( njoy::utility::copy( XS ) )
                    .energyGrid( ncBuilder.energyGrid() )
                   .add() // crossSection
                    .Q( Qvalue )
                    .angularDistribution()
                      .energyGrid( grid )
                      .isotropic()
                      .tabulated().interpolationFlag( f )
                                  .cosineGrid( njoy::utility::copy( cosine ) )
                                  .pdf( njoy::utility::copy( pdf ) )
                                  .cdf( njoy::utility::copy( cdf ) )
                        .add() 
                      .equiprobableCosineBins().values( 
                          njoy::utility::copy( cosineBins ) )
                        .add()
                    .add() // angular distribution
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
                  .add() // reaction
        );
      }
    }
    WHEN( "cross section length is less than full energy Grid length" ){
      std::vector< double > XS{ 1.0, 2.0 };
      THEN( "an exception is thrown if no energyGrid is given" ){
        CHECK_THROWS( 
          ncBuilder.reaction( MT )
                   .crossSection().values( njoy::utility::copy( XS ) )
                    .energyGrid( ncBuilder.energyGrid() )
                                  .add()
                   .Q( Qvalue )
                    .angularDistribution()
                      .energyGrid( grid )
                      .isotropic()
                      .tabulated().interpolationFlag( f )
                                  .cosineGrid( njoy::utility::copy( cosine ) )
                                  .pdf( njoy::utility::copy( pdf ) )
                                  .cdf( njoy::utility::copy( cdf ) )
                        .add() 
                      .equiprobableCosineBins().values( 
                          njoy::utility::copy( cosineBins ) )
                        .add()
                   .add()
        );
      }
      THEN( "an exception is thrown if energyGrid is the wrong size" ){
        CHECK_THROWS( 
          ncBuilder.reaction( MT )
                   .crossSection().values( njoy::utility::copy( XS ) )
                    .energyGrid( ncBuilder.energyGrid() )
                                 .add()
                   .Q( Qvalue )
                    .angularDistribution()
                      .energyGrid( grid )
                      .isotropic()
                      .tabulated().interpolationFlag( f )
                                  .cosineGrid( njoy::utility::copy( cosine ) )
                                  .pdf( njoy::utility::copy( pdf ) )
                                  .cdf( njoy::utility::copy( cdf ) )
                        .add() 
                      .equiprobableCosineBins().values( 
                          njoy::utility::copy( cosineBins ) )
                        .add()
                   .add()
                    );
      } // THEN
      THEN( 
          "no exception is thrown when an appropriate energyGrid is given" ){
        CHECK_NOTHROW( 
          ncBuilder.reaction( MT )
                   .crossSection()
                      .values(  njoy::utility::copy( XS ) )
                      .energyGrid( njoy::ACEtk::Table::slice(
                                         ncBuilder.energyGrid() 
                                         | ranges::view::drop( 1 )
                                     )
                                   )
                                  .add()
                      .Q( Qvalue )
                      .angularDistribution()
                        .energyGrid( grid )
                        .isotropic()
                        .tabulated().interpolationFlag( f )
                                    .cosineGrid( njoy::utility::copy( cosine ) )
                                    .pdf( njoy::utility::copy( pdf ) )
                                    .cdf( njoy::utility::copy( cdf ) )
                          .add() 
                        .equiprobableCosineBins().values( 
                            njoy::utility::copy( cosineBins ) )
                          .add()
                      .add()
                     );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
