#define CATCH_CONFIG_MAIN

#include <iostream>
#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Law67::AngularDistribution" ){
  int INTMU{ 3 };
  std::vector< double > energies{ 1.0, 2.0, 3.0 };

  int INTEP{ 3 };
  std::vector< double > dEnergies{ 10.0, 11.0, 12.0 };
  std::vector< double > PDF{ 0.2, 0.5, 0.3 };
  std::vector< double > CDF{ 0.2, 0.7, 1.0 };
  
  using Dist = ContinuousEnergyNeutron::SecondaryDistribution;
  std::vector< Dist > dists{
    Dist{ INTEP, dEnergies, PDF, CDF },
    Dist{ INTEP, dEnergies, PDF, CDF },
    Dist{ INTEP, dEnergies, PDF, CDF }
  };
  GIVEN( "valid input values" ){
    WHEN( "the angular distribution is constructed" ){
      ContinuousEnergyNeutron::Law67::AngularDistribution dist{
        INTMU, energies, std::move( dists ) };
      
      THEN( "the values can be verified" ){
        REQUIRE( INTMU == dist.interpolationParameter() );
        REQUIRE( INTMU == dist.INTMU() );
        REQUIRE( ranges::equal( energies, dist.energyGrid() ) );

        REQUIRE( 3 == dist.cosineDistributions().size() );
      }
    }
  } // GIVEN valid
  GIVEN( "invalid input values" ){
    WHEN( "wrong number of distributions" ){
      std::vector< Dist > dists{
        Dist{ INTEP, dEnergies, PDF, CDF },
        Dist{ INTEP, dEnergies, PDF, CDF },
        Dist{ INTEP, dEnergies, PDF, CDF },
        Dist{ INTEP, dEnergies, PDF, CDF }
      };

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( ContinuousEnergyNeutron::Law67::AngularDistribution( 
          INTMU, energies, std::move( dists ) ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO
