#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;
SCENARIO( "Testing interpretation::ContinuousEnergyNeutron::Builder" ){
  ContinuousEnergyNeutron::Builder ncBuilder{};

  GIVEN( "data for a reaction" ){
    std::vector< double > XS{ 1.0, 2.0, 3.0 };
    int MT{ 14 };
    WHEN( "adding a reaction" ){
      THEN( "no exception is thrown" ){
        CHECK_NOTHROW( ncBuilder.reaction( MT )
                                .crossSection( njoy::utility::copy( XS ) )
                                .add()
        );
      }
      WHEN( "adding a duplicate reaction" ){
        THEN( "an exception is thrown" ){
        ncBuilder.reaction( MT )
                 .crossSection( njoy::utility::copy( XS ) )
                 .add();
          CHECK_THROWS(
              ncBuilder.reaction( MT )
                       .crossSection( njoy::utility::copy( XS ) )
                       .add() 
          );
        }
      }
    }
  }
} // SCENARIO
