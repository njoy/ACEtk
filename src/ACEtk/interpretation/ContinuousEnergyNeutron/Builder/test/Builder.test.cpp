#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing ContinuousEnergyNeutron::Builder" ){
  ContinuousEnergyNeutron::Builder ncBuilder{};

  GIVEN( "data for the energy grid" ){
    std::vector< double > grid{1.0, 2.0, 3.0, 4.0, 5.0};
    ncBuilder.energyGrid( njoy::utility::copy( grid ) );

    THEN( "we can verify the energy grid" ){
      CHECK( ranges::equal( grid, ncBuilder.energyGrid() ) );
    }

    WHEN( "the energy grid has negative components" ){
      std::vector< double > grid{1.0, 2.0, 3.0, -4.0, 5.0};
      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS(
          ncBuilder.energyGrid( njoy::utility::copy( grid ) ),
          details::verify::exceptions::NotPositive&
          );
      }
    }
  }
  WHEN( "no energy grid has been given" ){
    THEN( "an exception is thrown when the energy grid is asked for" ){
      CHECK_THROWS( ncBuilder.energyGrid() );
    }
  }
  GIVEN( "data for a reaction" ){
    std::vector< double > XS{ 1.1, 2.1, 3.1 };
    std::vector< double > grid{1.0, 2.0, 3.0};
    double Qvalue{ 1.23 };
    ncBuilder.energyGrid( njoy::utility::copy( grid ) );

    int MT{ 14 };
    WHEN( "adding a reaction" ){
      THEN( "no exception is thrown" ){
        CHECK_NOTHROW( ncBuilder.reaction( MT )
                      .crossSection( njoy::utility::copy( XS ) )
                      .Q( Qvalue )
                      .add()
                     );
      }
    } // WHEN
    WHEN( "adding a duplicate reaction" ){
      THEN( "an exception is thrown" ){
        ncBuilder.reaction( MT )
                 .crossSection( njoy::utility::copy( XS ) )
                  .Q( Qvalue )
                 .add();
        CHECK_THROWS(
          ncBuilder.reaction( MT )
                    .crossSection( njoy::utility::copy( XS ) )
                    .Q( Qvalue )
                    .add() 
          );
      }
    }
    WHEN( "cross section length is less than full energy Grid length" ){
      std::vector< double > XS{ 1.0, 2.0 };
      THEN( "an exception is thrown if no energyGrid is given" ){
        CHECK_THROWS( ncBuilder.reaction( MT )
                     .crossSection( njoy::utility::copy( XS ) )
                     .Q( Qvalue )
                     .add()
                    );
      }
      THEN( "an exception is thrown if energyGrid is the wrong size" ){
        CHECK_THROWS( ncBuilder.reaction( MT )
                     .crossSection( njoy::utility::copy( XS ),
                                   ncBuilder.energyGrid() )
                     .Q( Qvalue )
                     .add()
                    );
      } // THEN
      THEN( 
          "no exception is thrown when an appropriate energyGrid is given" ){
        CHECK_NOTHROW( ncBuilder.reaction( MT )
                      .crossSection( njoy::utility::copy( XS ),
                                    njoy::ACEtk::Table::slice(
                                        ncBuilder.energyGrid() 
                                        | ranges::view::drop( 1 )
                                        )
                                   )
                      .Q( Qvalue )
                      .add()
                     );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

SCENARIO( "fissionMultiplicity components ofContinuousEnergyNeutron::Builder" ){
  ContinuousEnergyNeutron::Builder ncBuilder{};

  WHEN( "valid strings for nuType are used" ){
    std::vector< std::string > validnuTypes{ "total", "prompt", "delayed" };
    
    for( auto nuType : validnuTypes ){
      GIVEN( "polynomial fission multiplicity parameters: " + nuType ){
        std::vector< double > coefficients{ 1.0, 2.0, 5.0, 6.0 };

        if( nuType != "delayed" ){
          CHECK_NOTHROW( 
            ncBuilder.fissionMultiplicity( nuType )
                    .polynomial()
                    .coefficients( std::move( coefficients ) )
                    .add()
          );
        }
        if( nuType == "delayed" ){
          CHECK_THROWS( ncBuilder.fissionMultiplicity( nuType ) .polynomial() );
        }
      }
      GIVEN( "tabulated fission multiplicity parameters: " + nuType ){
        std::vector< double > boundaries{ 0.0, 3.0 };
        std::vector< double > schemes{ 2.0, 1.0 };
        std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
        std::vector< double > multiplicities{ 2.1, 2.2, 2.5, 2.5 };
        CHECK_NOTHROW( 
          ncBuilder.fissionMultiplicity( nuType )
                   .tabulated()
                   .boundaries( std::move( boundaries ) )
                   .schemes( std::move( schemes ) )
                   .energies( std::move( energies ) )
                   .multiplicities( std::move( multiplicities ) )
                   .add()
        );
      }
    }
  }
  WHEN( "invalid strings are used to create a fissionMultiplicity::Builder" ){
    std::vector< std::string > invalidnuTypes{ "abc", "prompts", "both" };

    for( auto nuType : invalidnuTypes ){
      THEN ( "an exception is thrown when nuType = " + nuType ){
        CHECK_THROWS_AS( 
          ncBuilder.fissionMultiplicity( nuType ),
          std::range_error&
        );
      }
    }
  }
} // SCENARIO

SCENARIO( "Photon Production components of ContinuousEnergyNeutron::Builder" ){
  ContinuousEnergyNeutron::Builder ncBuilder{};
  int MT{ 102 };
  WHEN( "valid MFS are used" ){
    {
      int MF = 12;
      std::vector< double > boundaries{ 0.0, 3.0 };
      std::vector< double > schemes{ 2.0, 1.0 };
      std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
      std::vector< double > values{ 2.1, 2.2, 2.5, 2.5 };

      ncBuilder.photonProduction( MF, MT )
               .yields()
               .boundaries ( njoy::utility::copy ( boundaries )  ) 
               .schemes    ( njoy::utility::copy ( schemes    )  ) 
               .energies   ( njoy::utility::copy ( energies   )  ) 
               .values     ( njoy::utility::copy ( values     )  ) ;
    }
    {
      int MF = 13;
      ncBuilder.photonProduction( MF, MT );
    }
    {
      int MF = 16;
      ncBuilder.photonProduction( MF, MT );
    }
  }
  WHEN( "invalid MFS are used" ){
    std::vector< int > invalidMFs{ 10, 11, 14, 15, 17, 18 };

    for( auto MF : invalidMFs ){
      THEN( "an exception is thrown when MF = " + std::to_string( MF ) ){
        CHECK_THROWS_AS(
          ncBuilder.photonProduction( MF, MT ),
          std::range_error&
        );
      }
    }
  }
  WHEN( "wrong sub-builder is called" ){
    THEN( "an exception is thrown" ){
      CHECK_THROWS_AS(
        ncBuilder.photonProduction( 13, MT ).yields(),
        std::range_error&
      );

    }
    THEN( "an exception is thrown" ){
      CHECK_THROWS_AS(
        ncBuilder.photonProduction( 12, MT ).crossSection(),
        std::range_error&
      );
      CHECK_THROWS_AS(
        ncBuilder.photonProduction( 16, MT ).crossSection(),
        std::range_error&
      );
    }
  }
}

SCENARIO( "adding gamma production data" ){
  ContinuousEnergyNeutron::Builder ncBuilder{};
  std::vector< double > XS{ 1.0, 2.0, 3.0 };
  std::array< std::array< double, 20 >, 30 > energies{{
      0.00,  0.01,  0.02,  0.03,  0.04,  0.05,  0.06,  0.07,  0.08,  0.09,
      0.10,  0.11,  0.12,  0.13,  0.14,  0.15,  0.16,  0.17,  0.18,  0.19,

      1.00,  1.01,  1.02,  1.03,  1.04,  1.05,  1.06,  1.07,  1.08,  1.09,
      1.10,  1.11,  1.12,  1.13,  1.14,  1.15,  1.16,  1.17,  1.18,  1.19,

      2.00,  2.01,  2.02,  2.03,  2.04,  2.05,  2.06,  2.07,  2.08,  2.09,
      2.10,  2.11,  2.12,  2.13,  2.14,  2.15,  2.16,  2.17,  2.18,  2.19,

      3.00,  3.01,  3.02,  3.03,  3.04,  3.05,  3.06,  3.07,  3.08,  3.09,
      3.10,  3.11,  3.12,  3.13,  3.14,  3.15,  3.16,  3.17,  3.18,  3.19,

      4.00,  4.01,  4.02,  4.03,  4.04,  4.05,  4.06,  4.07,  4.08,  4.09,
      4.10,  4.11,  4.12,  4.13,  4.14,  4.15,  4.16,  4.17,  4.18,  4.19,

      5.00,  5.01,  5.02,  5.03,  5.04,  5.05,  5.06,  5.07,  5.08,  5.09,
      5.10,  5.11,  5.12,  5.13,  5.14,  5.15,  5.16,  5.17,  5.18,  5.19,

      6.00,  6.01,  6.02,  6.03,  6.04,  6.05,  6.06,  6.07,  6.08,  6.09,
      6.10,  6.11,  6.12,  6.13,  6.14,  6.15,  6.16,  6.17,  6.18,  6.19,

      7.00,  7.01,  7.02,  7.03,  7.04,  7.05,  7.06,  7.07,  7.08,  7.09,
      7.10,  7.11,  7.12,  7.13,  7.14,  7.15,  7.16,  7.17,  7.18,  7.19,

      8.00,  8.01,  8.02,  8.03,  8.04,  8.05,  8.06,  8.07,  8.08,  8.09,
      8.10,  8.11,  8.12,  8.13,  8.14,  8.15,  8.16,  8.17,  8.18,  8.19,

      9.00,  9.01,  9.02,  9.03,  9.04,  9.05,  9.06,  9.07,  9.08,  9.09,
      9.10,  9.11,  9.12,  9.13,  9.14,  9.15,  9.16,  9.17,  9.18,  9.19,

    10.00, 10.01, 10.02, 10.03, 10.04, 10.05, 10.06, 10.07, 10.08, 10.09,
    10.10, 10.11, 10.12, 10.13, 10.14, 10.15, 10.16, 10.17, 10.18, 10.19,

    11.00, 11.01, 11.02, 11.03, 11.04, 11.05, 11.06, 11.07, 11.08, 11.09,
    11.10, 11.11, 11.12, 11.13, 11.14, 11.15, 11.16, 11.17, 11.18, 11.19,

    12.00, 12.01, 12.02, 12.03, 12.04, 12.05, 12.06, 12.07, 12.08, 12.09,
    12.10, 12.11, 12.12, 12.13, 12.14, 12.15, 12.16, 12.17, 12.18, 12.19,

    13.00, 13.01, 13.02, 13.03, 13.04, 13.05, 13.06, 13.07, 13.08, 13.09,
    13.10, 13.11, 13.12, 13.13, 13.14, 13.15, 13.16, 13.17, 13.18, 13.19,

    14.00, 14.01, 14.02, 14.03, 14.04, 14.05, 14.06, 14.07, 14.08, 14.09,
    14.10, 14.11, 14.12, 14.13, 14.14, 14.15, 14.16, 14.17, 14.18, 14.19,

    15.00, 15.01, 15.02, 15.03, 15.04, 15.05, 15.06, 15.07, 15.08, 15.09,
    15.10, 15.11, 15.12, 15.13, 15.14, 15.15, 15.16, 15.17, 15.18, 15.19,

    16.00, 16.01, 16.02, 16.03, 16.04, 16.05, 16.06, 16.07, 16.08, 16.09,
    16.10, 16.11, 16.12, 16.13, 16.14, 16.15, 16.16, 16.17, 16.18, 16.19,

    17.00, 17.01, 17.02, 17.03, 17.04, 17.05, 17.06, 17.07, 17.08, 17.09,
    17.10, 17.11, 17.12, 17.13, 17.14, 17.15, 17.16, 17.17, 17.18, 17.19,

    18.00, 18.01, 18.02, 18.03, 18.04, 18.05, 18.06, 18.07, 18.08, 18.09,
    18.10, 18.11, 18.12, 18.13, 18.14, 18.15, 18.16, 18.17, 18.18, 18.19,

    19.00, 19.01, 19.02, 19.03, 19.04, 19.05, 19.06, 19.07, 19.08, 19.09,
    19.10, 19.11, 19.12, 19.13, 19.14, 19.15, 19.16, 19.17, 19.18, 19.19,

    20.00, 20.01, 20.02, 20.03, 20.04, 20.05, 20.06, 20.07, 20.08, 20.09,
    20.10, 20.11, 20.12, 20.13, 20.14, 20.15, 20.16, 20.17, 20.18, 20.19,

    21.00, 21.01, 21.02, 21.03, 21.04, 21.05, 21.06, 21.07, 21.08, 21.09,
    21.10, 21.11, 21.12, 21.13, 21.14, 21.15, 21.16, 21.17, 21.18, 21.19,

    22.00, 22.01, 22.02, 22.03, 22.04, 22.05, 22.06, 22.07, 22.08, 22.09,
    22.10, 22.11, 22.12, 22.13, 22.14, 22.15, 22.16, 22.17, 22.18, 22.19,

    23.00, 23.01, 23.02, 23.03, 23.04, 23.05, 23.06, 23.07, 23.08, 23.09,
    23.10, 23.11, 23.12, 23.13, 23.14, 23.15, 23.16, 23.17, 23.18, 23.19,

    24.00, 24.01, 24.02, 24.03, 24.04, 24.05, 24.06, 24.07, 24.08, 24.09,
    24.10, 24.11, 24.12, 24.13, 24.14, 24.15, 24.16, 24.17, 24.18, 24.19,

    25.00, 25.01, 25.02, 25.03, 25.04, 25.05, 25.06, 25.07, 25.08, 25.09,
    25.10, 25.11, 25.12, 25.13, 25.14, 25.15, 25.16, 25.17, 25.18, 25.19,

    26.00, 26.01, 26.02, 26.03, 26.04, 26.05, 26.06, 26.07, 26.08, 26.09,
    26.10, 26.11, 26.12, 26.13, 26.14, 26.15, 26.16, 26.17, 26.18, 26.19,

    27.00, 27.01, 27.02, 27.03, 27.04, 27.05, 27.06, 27.07, 27.08, 27.09,
    27.10, 27.11, 27.12, 27.13, 27.14, 27.15, 27.16, 27.17, 27.18, 27.19,

    28.00, 28.01, 28.02, 28.03, 28.04, 28.05, 28.06, 28.07, 28.08, 28.09,
    28.10, 28.11, 28.12, 28.13, 28.14, 28.15, 28.16, 28.17, 28.18, 28.19,

    29.00, 29.01, 29.02, 29.03, 29.04, 29.05, 29.06, 29.07, 29.08, 29.09,
    29.10, 29.11, 29.12, 29.13, 29.14, 29.15, 29.16, 29.17, 29.18, 29.19
  }};
  GIVEN( "valid cross section and energies" ){

    CHECK_NOTHROW(
      ncBuilder.totalGammaProduction()
               .crossSection( njoy::utility::copy( XS ) )
               .outgoingEnergies( njoy::utility::copy( energies ) )
               .add()
    );

  } // GIVEN
  GIVEN( "invalid cross section and energies" ){
  } // GIVEN
} // SCENARIO
