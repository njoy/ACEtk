#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Constructing a tabulated table for angular distribution" ){
  std::vector< int > validJJ{0, 1};
  std::vector< double > cos{ -0.6, -0.2, 0.2, 0.4, 1.0 };
  std::vector< double > PDF{ 0.1, 0.2, 0.3, 0.3, 0.1 };
  std::vector< double > CDF{ 0.1, 0.3, 0.6, 0.9, 1.0 };

  GIVEN( "valid input parameters" ){

    WHEN( "input parameters are consistent" ){
      for( auto JJ : validJJ ){

        ContinuousEnergyNeutron::angularDistribution::Tabulated tabu(
            JJ, cos, PDF, CDF );

        THEN( "the parameteters can be verified JJ=" + std::to_string(JJ) ){
          REQUIRE( JJ == tabu.interpolationFlag() );
          REQUIRE( 5 == tabu.PDF().size() );
          REQUIRE( 5 == tabu.cosineBins().size() );
          REQUIRE( ranges::equal( cos, tabu.cosineBins() ) );
          REQUIRE( ranges::equal( PDF, tabu.PDF() ) );
          REQUIRE( ranges::equal( CDF, tabu.CDF() ) );
        }
      }
    } // WHEN valid

    WHEN( "input parameters are incorrect or not consistent" ){
      WHEN( "interpolation flag is incorrect" ){
        std::vector< int > invalidJJ{-1,2};
        for( auto JJ : invalidJJ ){
          THEN( "an exception is thrown JJ=" + std::to_string(JJ) ){
            REQUIRE_THROWS_AS( 
              ContinuousEnergyNeutron::angularDistribution::Tabulated(
                  JJ, cos, PDF, CDF ),
              std::exception
            );
          }
        }
      }

      WHEN( "cos bins are not the right length" ){
        std::vector< double > invalidCos{ -0.6, -0.2, 0.2, 0.4 };
        THEN( "an exception is thrown" ){
          REQUIRE_THROWS_AS( 
            ContinuousEnergyNeutron::angularDistribution::Tabulated(
                0, invalidCos, PDF, CDF ),
            std::range_error
          );
        }
      }

    } // WHEN invalid
  } // GIVEN
} // SCENARIO
