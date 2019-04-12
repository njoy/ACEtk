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

    std::vector< double > elasticXS{ 
      0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2 };

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
        .add(); // reaction 16
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
          .Q( -5.297781 )
          .crossSection()
            .values( XS )
            .energyGrid( nc.energyGrid() )
          .add()  // crossSection
          .neutronYield( 2, 
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
      std::vector< int > boundaries{ 0, 3 };
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
          .neutronYield( 19, 
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

      nc.reaction( 102 )
          .Q( 6.5452 )
          .crossSection()
            .values( XS )
            .energyGrid( nc.energyGrid() )
          .add() // crossSection
          // No angularDistribution
          // No energyDistribution
        .add(); // reaction 102

      // Photon production reaction
      std::vector< int > boundaries{ 0, 3 };
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

        {{ 1.00, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09,
        1.10, 1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19,
        1.20, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29,
        1.30, 1.31, 1.32 }},

        {{ 2.00, 2.01, 2.02, 2.03, 2.04, 2.05, 2.06, 2.07, 2.08, 2.09,
        2.10, 2.11, 2.12, 2.13, 2.14, 2.15, 2.16, 2.17, 2.18, 2.19,
        2.20, 2.21, 2.22, 2.23, 2.24, 2.25, 2.26, 2.27, 2.28, 2.29,
        2.30, 2.31, 2.32 }}
      };
      std::vector< double > grid{ 1.0, 2.0, 3.0, 4.0 };
      nc.photonProductionReaction( 12, 102 )
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
        .add(); // photonProductionReaction
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
        .CDFs( njoy::utility::copy( CDFs ) )
        .totalCrossSections( njoy::utility::copy( totalXS ) )
        .elasticCrossSections( njoy::utility::copy( elasticXS ) )
        .fissionCrossSections( njoy::utility::copy( fissionXS ) )
        .captureCrossSections( njoy::utility::copy( captureXS ) )
        .heating( njoy::utility::copy( heating ) )
      .add(); // probabilityTable
    }

    WHEN( "constructing a Table" ){

      auto table = nc.construct();

      auto header = table.header;
      auto data = table.data;

      THEN( "the NXS array can be checked " ){
        size_t size{ 123 };
        CHECK( size == data.XSS().size() );

        CHECK( size == data.NXS( 1 ) );
        CHECK( ZA == data.NXS( 2 ) );
        CHECK( 10 == data.NXS(  3 ) );
        CHECK( 3 == data.NXS(  4 ) );
        // CHECK( 10 == data.NXS(  5 ) );
        // CHECK( 10 == data.NXS(  6 ) );
        CHECK( 0 == data.NXS(  7 ) );
        CHECK( 1 == data.NXS(  8 ) );
        // CHECK( 0 == data.NXS(  9 ) );
        // CHECK( 0 == data.NXS( 10 ) );
        // CHECK( 0 == data.NXS( 11 ) );
        CHECK( 0 == data.NXS( 12 ) );
        CHECK( 0 == data.NXS( 13 ) );
        CHECK( 0 == data.NXS( 14 ) );
        CHECK( 0 == data.NXS( 15 ) );
        CHECK( 0 == data.NXS( 16 ) );
      }
      THEN( "the JXS array can be checked " ){
        CHECK( 1  == data.JXS( 1  ) );
        CHECK( 51 == data.JXS( 2  ) );
        CHECK( 83 == data.JXS( 3  ) );
        CHECK( 86 == data.JXS( 4  ) );
        CHECK( 89 == data.JXS( 5  ) );
        CHECK( 92 == data.JXS( 6  ) );
        CHECK( 95 == data.JXS( 7  ) );
        // CHECK( 0 == data.JXS( 8  ) );
        // CHECK( 0 == data.JXS( 9  ) );
        // CHECK( 0 == data.JXS( 10 ) );
        // CHECK( 0 == data.JXS( 11 ) );
        // CHECK( 0 == data.JXS( 12 ) );
        // CHECK( 0 == data.JXS( 13 ) );
        // CHECK( 0 == data.JXS( 14 ) );
        // CHECK( 0 == data.JXS( 15 ) );
        // CHECK( 0 == data.JXS( 16 ) );
        // CHECK( 0 == data.JXS( 17 ) );
        // CHECK( 0 == data.JXS( 18 ) );
        // CHECK( 0 == data.JXS( 19 ) );
        // CHECK( 0 == data.JXS( 20 ) );
        // CHECK( 0 == data.JXS( 21 ) );
        // CHECK( 0 == data.JXS( 22 ) );
        // CHECK( 0 == data.JXS( 23 ) );
        // CHECK( 0 == data.JXS( 24 ) );
        // CHECK( 0 == data.JXS( 25 ) );
        CHECK( 67 == data.JXS( 26 ) );
        // CHECK( 0 == data.JXS( 27 ) );
        CHECK( 0 == data.JXS( 28 ) );
        CHECK( 0 == data.JXS( 29 ) );
        CHECK( 0 == data.JXS( 30 ) );
        CHECK( 0 == data.JXS( 31 ) );
        CHECK( 0 == data.JXS( 32 ) );
      }

      // njoy::Log::info( "xss: {}", data.XSS() | ranges::view::all );

      int NTR = data.NXS( 4 );

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
        std::vector< double > mtrRef{ 16, 18, 102 };
        auto mtr = data.XSS( data.JXS( 3 ), NTR );

        CHECK( ranges::equal( mtrRef, mtr ) );
      }
      THEN( "the LQR Block can be checked" ){
        std::vector< double > lqrRef{ -5.297781, 7.0, 6.5452 };
        auto lqr = data.XSS( data.JXS( 4 ), NTR );

        CHECK( ranges::equal( lqrRef, lqr ) );
      }
      THEN( "the TYR Block can be checked" ){
        std::vector< double > tyrRef{ -2, 19, 0 };
        auto tyr = data.XSS( data.JXS( 5 ), NTR );

        CHECK( ranges::equal( tyrRef, tyr ) );
      }
      THEN( "the LSIG Block can be checked" ){
        std::vector< double > lsigRef{ 1, 13, 18, 30 };
        auto lsig = data.XSS( data.JXS( 6 ), NTR );

        njoy::Log::info( "lsigR: {}" , lsigRef | ranges::view::all );
        njoy::Log::info( "lsig : {}" , lsig | ranges::view::all );
        CHECK( ranges::equal( lsigRef, lsig ) );
      }

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
            .Q( -5.297781 )
            .crossSection()
              .values( XS )
              .energyGrid( nc.energyGrid() )
            .add()  // crossSection
            .neutronYield( 2, 
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
        std::vector< int > boundaries{ 0, 3 };
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
            .neutronYield( 19, 
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

        nc.reaction( 102 )
            .Q( 6.5452 )
            .crossSection()
              .values( XS )
              .energyGrid( nc.energyGrid() )
            .add() // crossSection
            // No angularDistribution
            // No energyDistribution
          .add(); // reaction 102

        // Photon production reaction
        std::vector< int > boundaries{ 0, 3 };
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

          {{ 1.00, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09,
          1.10, 1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19,
          1.20, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29,
          1.30, 1.31, 1.32 }},

          {{ 2.00, 2.01, 2.02, 2.03, 2.04, 2.05, 2.06, 2.07, 2.08, 2.09,
          2.10, 2.11, 2.12, 2.13, 2.14, 2.15, 2.16, 2.17, 2.18, 2.19,
          2.20, 2.21, 2.22, 2.23, 2.24, 2.25, 2.26, 2.27, 2.28, 2.29,
          2.30, 2.31, 2.32 }}
        };
        std::vector< double > grid{ 1.0, 2.0, 3.0, 4.0 };
        nc.photonProductionReaction( 12, 102 )
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
          .add(); // photonProductionReaction
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
          .CDFs( njoy::utility::copy( CDFs ) )
          .totalCrossSections( njoy::utility::copy( totalXS ) )
          .elasticCrossSections( njoy::utility::copy( elasticXS ) )
          .fissionCrossSections( njoy::utility::copy( fissionXS ) )
          .captureCrossSections( njoy::utility::copy( captureXS ) )
          .heating( njoy::utility::copy( heating ) )
        .add(); // probabilityTable
      }

      THEN( "an exception is thrown" ){

        CHECK_THROWS( nc.construct());

      }
    } // 
  } // GIVEN invalid
} // SCENARIO complete
