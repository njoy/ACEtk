#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Complete ContinuousEnergyNeutron::Builder" ){
  ContinuousEnergyNeutron::Builder nc{};

  GIVEN( "valid data" ){
    std::string zaid{ "92235.100nc" };
    nc.header()
         .processDate( date::year{2019}/3/14 )
         .temperature( 2.5301E-8*dimwits::mega( electronVolts ) )
         .atomicWeightRatio( 233.024800 )
         .zaid( zaid )
         .source( "ENDF/B-77.9" ) 
      .add(); // header

    std::vector< double > energyGrid{ 
      0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    nc.energyGrid( njoy::utility::copy( energyGrid ) );

    std::vector< double > totalXS{ 
      10.0, 10.1, 10.2, 10.3, 10.4, 10.5, 10.6, 10.7, 10.8, 10.9 };
    nc.totalCrossSection( njoy::utility::copy( totalXS ) );

    std::vector< double > heating{ 
      0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };
    nc.heating( njoy::utility::copy( heating ) );

    std::vector< double > totalDisappearanceXS{ 
      7.0, 7.1, 7.2, 7.3, 7.4, 7.5, 7.6, 7.7, 7.8, 7.9 };
    nc.totalDisappearanceCrossSection( 
        njoy::utility::copy( totalDisappearanceXS ) );

    std::vector< double > totalGammaXS{
      0.9, 1.9, 2.9, 3.9, 4.9, 5.9, 6.9, 7.9, 8.9, 9.9 };
    nc.totalGammaProduction()
         .crossSection( njoy::utility::copy( totalGammaXS ) )
      .add();

    std::vector< double > totalFissionXS{ 4.18, 5.18, 6.18, 7.18, 8.18, 9.18 };
    decltype( auto ) grid = nc.energyGrid();
    auto fEnergies = grid | ranges::view::slice( 4l, ranges::distance( grid ) );
    nc.totalFissionCrossSection()
        .values( njoy::utility::copy( totalFissionXS ) )
        .energyGrid( fEnergies )
      .add();

    std::vector< double > elasticXS{ 
      0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2 };

    int ZA{ 92235 };
    nc.SZA( ZA );

    { // nubar 
      std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
      std::vector< double > multiplicities{ 2.1, 2.2, 2.5, 2.5 };
      std::vector< double > coefficients{ 1.0, 2.0, 5.0, 6.0 };
      std::vector< double > probabilities{ 0.1, 0.2, 0.5, 0.2 };
      { // prompt
        nc.fissionMultiplicity( "prompt" )
           .polynomial()
             .coefficients( njoy::utility::copy( coefficients ) )
          .add(); // fissionMultiplicity (prompt)
      }
      { // delayed
        nc.fissionMultiplicity( "delayed" )
          .tabulated()
            .energies( njoy::utility::copy( energies ) )
            .multiplicities( njoy::utility::copy( multiplicities ) )
          .add(); // prompt nubar

      }
      { // delayed precursors
        nc.precursors()
            .energies( njoy::utility::copy( energies ) )
            .probabilities( njoy::utility::copy( coefficients ) )
            .decayConstant( 1.5E-4 )
            .energyDistribution()
              .energies( njoy::utility::copy( energies ) )
              .probabilities( njoy::utility::copy( probabilities ) )
              .levelScattering()
                .atomicWeightRatio( 235.98 )
                .QValue( 2.765 )
              .add() // levelScattering
            .add() // energyDistribution
          .add(); // precursors
      }
    }
    { // MT=2

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

      nc.reaction( 2 )
          .Q( 0.0 )
          .crossSection()
            .values( njoy::utility::copy( elasticXS ) )
            .energyGrid( nc.energyGrid() )
          .add()  // crossSection
          .neutronYield( 2 )
          .neutronYieldReferenceFrame(
            ContinuousEnergyNeutron::Builder::
                NeutronYieldReferenceFrame::CENTEROFMASS )
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
        .add(); // reaction 2
    }
    /*
    { // MT=4

      // Angular distribution
      std::vector< double > grid{ 1.0, 2.0, 3.0, 4.0, 5.0 };
      std::vector< double > inelasticXS{ 
        0.4, 1.4, 2.4, 3.4, 4.4, 5.4, 6.4, 7.4, 8.4, 9.4 };

      nc.reaction( 2 )
          .Q( 0.0 )
          .crossSection()
            .values( njoy::utility::copy( inelasticXS ) )
            .energyGrid( nc.energyGrid() )
          .add()  // crossSection
        .add(); // reaction 16
    }
    */
    { // MT=5
      std::vector< double > XS{ 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5 };
      auto grid = nc.energyGrid();
      auto xsEnergies = grid 
        | ranges::view::slice( 3l, ranges::distance( grid ) );

      auto rB = nc.reaction( 5 );
        rB.Q( 3.265 )
          .crossSection()
            .values( njoy::utility::copy( XS ) )
            .energyGrid( xsEnergies )
          .add();  // crossSection
          // no angular distribution

        rB.neutronYield( 0 )
          .neutronYieldReferenceFrame(
            ContinuousEnergyNeutron::Builder::
                NeutronYieldReferenceFrame::CENTEROFMASS );

        { // Energy distribution
          std::vector< int > boundaries{ 1, 3 };
          std::vector< int > schemes{ 2, 1 };
          std::vector< double > energies{ 1.0, 2.0 };
          std::vector< double > probabilities{ 0.1, 0.2 };
          std::vector< int > INTT{ 1, 2 };
          std::vector< double > ene{ 1.0, 2.0};
          std::vector< double > pdf{ 0.25, 0.75 };
          std::vector< double > cdf{ 0.25, 1.0 };
          std::vector< double > R{ 0.99, 0.01 };
          std::vector< double > A{ 0.75, 0.22 };

          rB.energyDistribution()
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
            .add();  // energyDistribution
        }
        { // Photon production
          std::vector<double > ppGrid{ 1.0, 2.0, 5.0, 10.0 };
          std::vector< double > ppXS{ 1.0, 2.0, 3.0, 4.0 };
          std::vector< int > boundaries{ 1, 3 };
          std::vector< int > schemes{ 2, 1 };
          std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
          std::vector< double > values{ 2.1, 2.2, 2.5, 2.5 };
          std::vector< double > probabilities{ 0.1, 0.2, 0.5, 0.2 };
          std::vector< double > ene{ 1.0, 2.0, 3.0};
          std::vector< int > INTT{ 1, 2 };
          std::vector< double > pdf{ 0.1, 0.5, 0.4 };
          std::vector< double > cdf{ 0.1, 0.6, 1.0 };

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

          rB.photonProduction( 13 )
              .crossSection()
                .values( njoy::utility::copy( ppXS ) )
                .energyGrid( ppGrid 
                  | ranges::view::slice( 0l, ranges::distance( ppGrid ) ) )
              .add() // crossSection
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
                  .add() // distributionData
                  .distributionData()
                    .interpolationParameter( INTT[ 1 ] )
                    .energies( njoy::utility::copy( ene ) )
                    .pdf( njoy::utility::copy( pdf ) )
                    .cdf( njoy::utility::copy( cdf ) )
                  .add() // distributionData
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
                .add() // continuousTabularDistribution LAW=4
              .add() // energy distribution
            .add(); // photonProduction
        }
        { // Energy-dependent neutron yields
          std::vector< int > boundaries{ 1, 3 };
          std::vector< int > schemes{ 2, 1 };
          std::vector< double > energies{ 1.0, 2.0 };
          std::vector< double > yields{ 1.45, 2.35 };

          rB.energyDependentNeutronYields()
              .boundaries( njoy::utility::copy( boundaries ) )
              .schemes( njoy::utility::copy( schemes ) )
              .energies( njoy::utility::copy( energies ) )
              .yields( njoy::utility::copy( yields ) )
            .add(); // energyDependentNeutronYields

        }

        rB.add(); // reaction 5
    }
    { // MT=16
      std::vector< double > XS{ 
        0.16, 1.16, 2.16, 3.16, 4.16, 5.16, 6.16, 7.16, 8.16, 9.16 };

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
      std::vector< int > boundaries{ 1, 3 };
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
          .Q( -5.297781 )
          .crossSection()
            .values( XS )
            .energyGrid( nc.energyGrid() )
          .add()  // crossSection
          .neutronYield( 2 )
          .neutronYieldReferenceFrame(
            ContinuousEnergyNeutron::Builder::
                NeutronYieldReferenceFrame::CENTEROFMASS )
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
    { // MT=18

      std::vector< double > XS{ 7.18, 8.18, 9.18 };
      auto grid = nc.energyGrid();
      auto xsEnergies = grid 
        | ranges::view::slice( 7l, ranges::distance( grid ) );

      // Energy distribution
      std::vector< int > boundaries{ 1, 3 };
      std::vector< int > schemes{ 2, 1 };
      std::vector< double > energies{ 1.0, 2.0 };
      std::vector< double > probabilities{ 0.1, 0.2 };
      std::vector< int > INTT{ 1, 2 };
      std::vector< double > ene{ 1.0, 2.0};
      std::vector< double > pdf{ 0.25, 0.75 };
      std::vector< double > cdf{ 0.25, 1.0 };

      nc.reaction( 18 )
          .Q( 7.0 )
          .crossSection()
            .values( XS )
            // .energyGrid( nc.energyGrid() )
            .energyGrid( xsEnergies )
          .add() // crossSection
          .neutronYield( 19 )
          .neutronYieldReferenceFrame(
            ContinuousEnergyNeutron::Builder::
                NeutronYieldReferenceFrame::LAB )
          // Isotropic---no angular distribution needed
          .energyDistribution()
            .energies( std::move( energies ) )
            .probabilities( std::move( probabilities ) )
            .continuousTabularDistribution()
              .energies( std::move( energies ) )
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
            .add() // continuousTabularDistribution
          .add() // energyDistribution
        .add(); // reaction 18
    }
    { // MT 102
      std::vector< double > XS{ 
        0.102, 1.102, 2.102, 3.102, 4.102, 5.102, 6.102, 7.102, 8.102, 9.102 };

      // Photon production reaction
      std::vector< int > boundaries{ 1, 3 };
      std::vector< int > schemes{ 2, 1 };
      std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
      std::vector< double > values{ 2.1, 2.2, 2.5, 2.5 };
      std::vector< double > probabilities{ 0.1, 0.2, 0.5, 0.2 };
      std::vector< double > ene{ 1.0, 2.0, 3.0};
      std::vector< int > INTT{ 1, 2 };
      std::vector< double > pdf{ 0.1, 0.5, 0.4 };
      std::vector< double > cdf{ 0.1, 0.6, 1.0 };

      std::vector< double > ppXS{ 
        0.6102, 1.6102, 2.6102, 3.6102, 4.6102, 
        5.6102, 6.6102, 7.6102, 8.6102, 9.6102 };
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

      nc.reaction( 102 )
          .Q( 6.5452 )
          .crossSection()
            .values( XS )
            .energyGrid( nc.energyGrid() )
          .add() // crossSection
          // No angularDistribution
          // No energyDistribution
          .photonProduction( 12 )
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
                .add() // distributionData
                .distributionData()
                  .interpolationParameter( INTT[ 1 ] )
                  .energies( njoy::utility::copy( ene ) )
                  .pdf( njoy::utility::copy( pdf ) )
                  .cdf( njoy::utility::copy( cdf ) )
                .add() // distributionData
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
              .add() // continuousTabularDistribution LAW=4
            .add() // energy distribution
          .add()  // photonProduction
        .add(); // reaction 102
    }
    { // probability tables
      int INT{ 2 };
      int inelasticCompetition{ 3 };
      int otherAbsorption{ 54 };
      ContinuousEnergyNeutron::Builder::Factors factors{ 
        ContinuousEnergyNeutron::Builder::Factors::CROSSSECTIONS };
      std::vector< double > energies{ 1.0, 2.0, 3.0 };
      std::vector< double > CDFs{ 0.1, 0.4, 1.0 };
      std::vector< double > totalXS{ 10, 20, 30 };
      std::vector< double > elasticXS{ 11, 21, 31 };
      std::vector< double > fissionXS{ 12, 22, 32 };
      std::vector< double > captureXS{ 13, 23, 33 };
      std::vector< double > heating{ 14, 24, 34 };
      
      nc.probabilityTable()
          .interpolationParameter( INT )
          .inelasticCompetition( inelasticCompetition )
          .otherAbsorption( otherAbsorption )
          .factors( factors )
          .incidentEnergies( njoy::utility::copy( energies ) )
          .table()
            .CDFs( njoy::utility::copy( CDFs ) )
            .totalCrossSections( njoy::utility::copy( totalXS ) )
            .elasticCrossSections( njoy::utility::copy( elasticXS ) )
            .fissionCrossSections( njoy::utility::copy( fissionXS ) )
            .captureCrossSections( njoy::utility::copy( captureXS ) )
            .heating( njoy::utility::copy( heating ) )
          .add() // table
          .table()
            .CDFs( njoy::utility::copy( CDFs ) )
            .totalCrossSections( njoy::utility::copy( totalXS ) )
            .elasticCrossSections( njoy::utility::copy( elasticXS ) )
            .fissionCrossSections( njoy::utility::copy( fissionXS ) )
            .captureCrossSections( njoy::utility::copy( captureXS ) )
            .heating( njoy::utility::copy( heating ) )
          .add()
          .table()
            .CDFs( njoy::utility::copy( CDFs ) )
            .totalCrossSections( njoy::utility::copy( totalXS ) )
            .elasticCrossSections( njoy::utility::copy( elasticXS ) )
            .captureCrossSections( njoy::utility::copy( captureXS ) )
          .add()
        .add(); // probabilityTable
    }

    WHEN( "constructing a Table" ){

      auto start = std::chrono::high_resolution_clock::now();
      auto table = nc.construct();
      auto finish = std::chrono::high_resolution_clock::now();
      std::chrono::duration< double > elapsed = finish - start;
      njoy::Log::info( "Time required to construct ACE Table: {} (ms)", 
                       elapsed.count()*1000 );

      auto header = table.header;
      auto data = table.data;

      THEN( "the NXS array can be checked " ){
        long long size{ 862 };
        CHECK( size == data.XSS().size() );

        CHECK( size == data.NXS( 1 ) );
        CHECK( ZA  == data.NXS(  2 ) );
        CHECK( 10  == data.NXS(  3 ) );
        CHECK( 4   == data.NXS(  4 ) );
        CHECK( 3   == data.NXS(  5 ) );
        CHECK( 2   == data.NXS(  6 ) );
        CHECK( 0   == data.NXS(  7 ) );
        CHECK( 1   == data.NXS(  8 ) );
        CHECK( 0   == data.NXS(  9 ) );
        CHECK( 92  == data.NXS( 10 ) );
        CHECK( 235 == data.NXS( 11 ) );
        CHECK( 0   == data.NXS( 12 ) );
        CHECK( 0   == data.NXS( 13 ) );
        CHECK( 0   == data.NXS( 14 ) );
        CHECK( 0   == data.NXS( 15 ) );
        CHECK( 0   == data.NXS( 16 ) );
      }
      THEN( "the JXS array can be checked " ){
        CHECK( 1   == data.JXS( 1  ) );
        CHECK( 51  == data.JXS( 2  ) );
        CHECK( 84  == data.JXS( 3  ) );
        CHECK( 88  == data.JXS( 4  ) );
        CHECK( 382 == data.JXS( 5  ) );
        CHECK( 92  == data.JXS( 6  ) );
        CHECK( 96  == data.JXS( 7  ) );
        CHECK( 134 == data.JXS( 8  ) );
        CHECK( 138 == data.JXS( 9  ) );
        CHECK( 248 == data.JXS( 10 ) );
        CHECK( 251 == data.JXS( 11 ) );
        CHECK( 386 == data.JXS( 12 ) );
        CHECK( 396 == data.JXS( 13 ) );
        CHECK( 398 == data.JXS( 14 ) );
        CHECK( 400 == data.JXS( 15 ) );
        CHECK( 423 == data.JXS( 16 ) );
        CHECK( 425 == data.JXS( 17 ) );
        CHECK( 637 == data.JXS( 18 ) );
        CHECK( 639 == data.JXS( 19 ) );
        CHECK( 789 == data.JXS( 20 ) );
        CHECK( 792 == data.JXS( 21 ) );
        CHECK( 0   == data.JXS( 22 ) );
        CHECK( 800 == data.JXS( 23 ) );
        CHECK( 57  == data.JXS( 24 ) );
        CHECK( 0   == data.JXS( 25 ) );
        CHECK( 68  == data.JXS( 26 ) );
        CHECK( 69  == data.JXS( 27 ) );
        CHECK( 0   == data.JXS( 28 ) );
        CHECK( 0   == data.JXS( 29 ) );
        CHECK( 0   == data.JXS( 30 ) );
        CHECK( 0   == data.JXS( 31 ) );
        CHECK( 0   == data.JXS( 32 ) );
      }

      int NTR = data.NXS( 4 );
      int NR = data.NXS( 5 );
      int NTRP = data.NXS( 6 );

      THEN( "the ESZ Block can be checked" ){
        auto ESZ = data.JXS( 1 );
        auto NES = data.NXS( 3 );

        CHECK( ranges::equal( energyGrid, data.XSS( ESZ + 0*NES, NES ) ) );
        CHECK( ranges::equal( totalXS,    data.XSS( ESZ + 1*NES, NES ) ) );
        CHECK( ranges::equal( totalDisappearanceXS,
                                          data.XSS( ESZ + 2*NES, NES ) ) );
        CHECK( ranges::equal( elasticXS,  data.XSS( ESZ + 3*NES, NES ) ) );
        CHECK( ranges::equal( heating,    data.XSS( ESZ + 4*NES, NES ) ) );
      }
      THEN( "the MTR Block can be checked" ){
        std::vector< double > mtrRef{ 5, 16, 18, 102 };
        auto mtr = data.XSS( data.JXS( 3 ), NTR );

        CHECK( ranges::equal( mtrRef, mtr ) );
      }
      THEN( "the LQR Block can be checked" ){
        std::vector< double > lqrRef{ 3.265, -5.297781, 7.0, 6.5452 };
        auto lqr = data.XSS( data.JXS( 4 ), NTR );

        CHECK( ranges::equal( lqrRef, lqr ) );
      }
      THEN( "the TYR Block can be checked" ){
        std::vector< double > tyrRef{ 0, -2, 19, 0 };
        auto tyr = data.XSS( data.JXS( 5 ), NTR );

        CHECK( ranges::equal( tyrRef, tyr ) );
      }
      THEN( "the LSIG Block can be checked" ){
        std::vector< double > lsigRef{ 1, 10, 22, 27 };
        auto lsig = data.XSS( data.JXS( 6 ), NTR );

        CHECK( ranges::equal( lsigRef, lsig ) );
      }
      THEN( "the LAND Block can be checked" ){
        std::vector< double > landRef{ 1, 0, 56, 0 };
        auto land = data.XSS( data.JXS( 8 ), NR  + 1);

        CHECK( ranges::equal( landRef, land ) );
      }
      THEN( "the LDLW Block can be checked " ){
        std::vector< double > ldlwRef{ 11, 56, 101 };
        auto ldlw = data.XSS( data.JXS( 10 ), NR );

        CHECK( ranges::equal( ldlwRef, ldlw ) );
      }
      THEN( "the MTRP Block can be checked" ){
        std::vector< double > mtrpRef{ 5, 102 };
        auto mtrp = data.XSS( data.JXS( 13 ), NTRP );

        CHECK( ranges::equal( mtrpRef, mtrp ) );
      }
      THEN( "the LSIGP Block can be checked " ){
        std::vector< double > lsigpRef{ 1, 8 };
        auto lsigp = data.XSS( data.JXS( 14 ), NTRP );

        CHECK( ranges::equal( lsigpRef, lsigp ) );
      }
      THEN( "the LANDP Block can be checked" ){
        std::vector< double > landpRef{ 1, 107 };
        auto landp = data.XSS( data.JXS( 16 ), NTRP );

        CHECK( ranges::equal( landpRef, landp ) );
      }
      THEN( "the LDLWP Block can be checked " ){
        std::vector< double > ldlwpRef{ 1, 76 };
        auto ldlwp = data.XSS( data.JXS( 18 ), NTRP );

        CHECK( ranges::equal( ldlwpRef, ldlwp ) );
      }
      THEN( "the YP Block can be checked" ){
        std::vector< double > yppRef{ 2, 5, 102 };
        auto ypp = data.XSS( data.JXS( 20 ), 3 );

        CHECK( ranges::equal( yppRef, ypp ) );
      }
      THEN( "the FIS Block can be checked" ){
        std::vector< double > fisRef{};
        fisRef.push_back( 5 );
        fisRef.push_back( 6 );
        fisRef |= ranges::action::push_back( totalFissionXS );

        auto fis = data.XSS( data.JXS( 21 ), 8 );

        CHECK( ranges::equal( fisRef, fis ) );
      }
      THEN( "the UNR Block can be checked" ){
        std::vector< double > unrRef{};
        unrRef.push_back( 3 );      // N
        unrRef.push_back( 3 );      // M
        unrRef.push_back( 2 );      // INT
        unrRef.push_back( 3 );      // ILF
        unrRef.push_back( 54 );     // IOA
        unrRef.push_back( 0 );      // IFF
        unrRef.push_back( 1.0 );    // energies
        unrRef.push_back( 2.0 );
        unrRef.push_back( 3.0 );
        unrRef.push_back( 0.1 );    // CDF_1
        unrRef.push_back( 0.4 );
        unrRef.push_back( 1.0 );
        unrRef.push_back( 10 );    // total_1
        unrRef.push_back( 20 );
        unrRef.push_back( 30 );
        unrRef.push_back( 11 );    // elastic_1
        unrRef.push_back( 21 );
        unrRef.push_back( 31 );
        unrRef.push_back( 12 );    // fission_1
        unrRef.push_back( 22 );
        unrRef.push_back( 32 );
        unrRef.push_back( 13 );    // capture_1
        unrRef.push_back( 23 );
        unrRef.push_back( 33 );
        unrRef.push_back( 14 );    // heating_1
        unrRef.push_back( 24 );
        unrRef.push_back( 34 );


        auto unr = data.XSS( data.JXS( 23 ), 27 );

        CHECK( ranges::equal( unrRef, unr ) );
      }

      // Print the Table to a file
      start = std::chrono::high_resolution_clock::now();

      std::ofstream aceFile;
      aceFile.open( zaid );
      table.print<2,0,1>( aceFile );
      aceFile.close();

      finish = std::chrono::high_resolution_clock::now();
      elapsed = finish - start;
      njoy::Log::info( "Time required to 'print' ACE Table: {} (ms)", 
                       elapsed.count()*1000 );

    }
  } // GIVEN valid
  GIVEN( "invalid data" ){
    WHEN( "SZA is negative" ){
      int SZA{ -5 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS( nc.SZA( SZA ) );
      }
    }
    WHEN( "heating data is negative" ){
      std::vector< double > heating{ 
        0.0, 0.1, -0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          nc.heating( heating ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "various data is the wrong length" ){
      std::vector< double > energyGrid{ 
        0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
      nc.energyGrid( njoy::utility::copy( energyGrid ) );

      THEN( "an exception is thrown" ){
        std::vector< double > totalXS{ 
          10.0, 10.1, 10.2, 10.3, 10.4, 10.5, 10.6, 10.7, 10.8 };
        nc.totalCrossSection( njoy::utility::copy( totalXS ) );

        CHECK_THROWS_AS(
          nc.construct(),
          std::range_error&
        );

        AND_THEN( "an exception is thrown" ){
          std::vector< double > heating{ 
            0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8 };
          nc.heating( njoy::utility::copy( heating ) );

          CHECK_THROWS_AS(
            nc.construct(),
            std::range_error&
          );
          AND_THEN( "an exception is thrown" ){
            std::vector< double > totalDisappearanceXS{ 
              7.0, 7.1, 7.2, 7.3, 7.4, 7.5, 7.6, 7.7, 7.8 };
            nc.totalDisappearanceCrossSection( 
                njoy::utility::copy( totalDisappearanceXS ) );

            CHECK_THROWS_AS(
              nc.construct(),
              std::range_error&
            );
          }
        }
      }
    }
    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          nc.energyGrid( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          nc.energyGrid( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
    WHEN( "no scattering cross section is given" ){
      nc.header()
          .processDate( date::year{2019}/3/14 )
          .temperature( 2.5301E-8*dimwits::mega( electronVolts ) )
          .atomicWeightRatio( 233.024800 )
          .zaid( "92235.100nc" )
        .add(); // header

      std::vector< double > energyGrid{ 
        0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
      nc.energyGrid( njoy::utility::copy( energyGrid ) );

      std::vector< double > totalXS{ 
        10.0, 10.1, 10.2, 10.3, 10.4, 10.5, 10.6, 10.7, 10.8, 10.9 };
      nc.totalCrossSection( njoy::utility::copy( totalXS ) );

      std::vector< double > heating{ 
        0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };
      nc.heating( njoy::utility::copy( heating ) );

      std::vector< double > totalDisappearanceXS{ 
        7.0, 7.1, 7.2, 7.3, 7.4, 7.5, 7.6, 7.7, 7.8, 7.9 };
      nc.totalDisappearanceCrossSection( 
          njoy::utility::copy( totalDisappearanceXS ) );

      int ZA{ 92235 };
      nc.ZA( ZA );

      { // nubar 
        std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
        std::vector< double > multiplicities{ 2.1, 2.2, 2.5, 2.5 };
        std::vector< double > coefficients{ 1.0, 2.0, 5.0, 6.0 };
        std::vector< double > probabilities{ 0.1, 0.2, 0.5, 0.2 };
        { // prompt
          nc.fissionMultiplicity( "prompt" )
            .polynomial()
              .coefficients( njoy::utility::copy( coefficients ) )
            .add(); // fissionMultiplicity (prompt)
        }
        { // delayed
          nc.fissionMultiplicity( "delayed" )
            .tabulated()
              .energies( njoy::utility::copy( energies ) )
              .multiplicities( njoy::utility::copy( multiplicities ) )
            .add(); // prompt nubar

        }
        { // delayed precursors
          nc.precursors()
              .energies( njoy::utility::copy( energies ) )
              .probabilities( njoy::utility::copy( coefficients ) )
              .decayConstant( 1.5E-4 )
              .energyDistribution()
                .energies( njoy::utility::copy( energies ) )
                .probabilities( njoy::utility::copy( probabilities ) )
                .levelScattering()
                  .atomicWeightRatio( 235.98 )
                  .QValue( 2.765 )
                .add() // levelScattering
              .add() // energyDistribution
            .add(); // precursors
        }
      }
      { // MT=16
        std::vector< double > XS{ 
          0.16, 1.16, 2.16, 3.16, 4.16, 5.16, 6.16, 7.16, 8.16, 9.16 };

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
        std::vector< int > boundaries{ 1, 3 };
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
            .Q( -5.297781 )
            .crossSection()
              .values( XS )
              .energyGrid( nc.energyGrid() )
            .add()  // crossSection
            .neutronYield( 2 )
            .neutronYieldReferenceFrame( 
              ContinuousEnergyNeutron::Builder::
                  NeutronYieldReferenceFrame::CENTEROFMASS )
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
      { // MT=18

        std::vector< double > XS{ 
          0.18, 1.18, 2.18, 3.18, 4.18, 5.18, 6.18, 7.18, 8.18, 9.18 };
        
        // Energy distribution
        std::vector< int > boundaries{ 1, 3 };
        std::vector< int > schemes{ 2, 1 };
        std::vector< double > energies{ 1.0, 2.0 };
        std::vector< double > probabilities{ 0.1, 0.2 };
        std::vector< int > INTT{ 1, 2 };
        std::vector< double > ene{ 1.0, 2.0};
        std::vector< double > pdf{ 0.25, 0.75 };
        std::vector< double > cdf{ 0.25, 1.0 };

        nc.reaction( 18 )
            .Q( 1.934054E2 )
            .crossSection()
              .values( XS )
              .energyGrid( nc.energyGrid() )
            .add() // crossSection
            .neutronYield( 19 )
            .neutronYieldReferenceFrame(
              ContinuousEnergyNeutron::Builder::
                  NeutronYieldReferenceFrame::LAB )
            // Isotropic---no angular distribution needed
            .energyDistribution()
              .energies( std::move( energies ) )
              .probabilities( std::move( probabilities ) )
              .continuousTabularDistribution()
                .energies( std::move( energies ) )
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
              .add() // continuousTabularDistribution
            .add() // energyDistribution
          .add(); // reaction 18
      }

      THEN( "an exception is thrown" ){

        CHECK_THROWS( nc.construct());

      }
    } // 
  } // GIVEN invalid
} // SCENARIO complete
