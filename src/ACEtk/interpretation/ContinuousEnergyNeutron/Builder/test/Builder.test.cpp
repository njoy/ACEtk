#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;
SCENARIO( "Testing interpretation::ContinuousEnergyNeutron::Builder" ){
  ContinuousEnergyNeutron::Builder ncBuilder{};

  GIVEN( "data for the energy grid" ){
    std::vector< double > grid{1.0, 2.0, 3.0, 4.0, 5.0};
    ncBuilder.energyGrid( njoy::utility::copy( grid ) );

    THEN( "we can verify the energy grid" ){
      CHECK( ranges::equal( grid, ncBuilder.energyGrid() ) );
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
