#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

SCENARIO( "Law4" ){
  std::vector< double > NBT{ 1, 3 };
  std::vector< double > INT{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 3.0 };

  int INTT{ 3 };
  std::vector< double > dEnergies{ 10.0, 11.0, 12.0 };
  std::vector< double > PDF{ 0.2, 0.5, 0.3 };
  std::vector< double > CDF{ 0.2, 0.7, 1.0 };
  
  using Dist = ContinuousEnergyNeutron::ContinuousTabular::Distribution;
  std::vector< Dist > dists{
    Dist{ INTT, dEnergies, PDF, CDF },
    Dist{ INTT, dEnergies, PDF, CDF },
    Dist{ INTT, dEnergies, PDF, CDF }
  };

  GIVEN( "valid input values" ){
    WHEN( "constructing a LAW4" ){
      ContinuousEnergyNeutron::ContinuousTabular law4( 
        NBT, INT, energies, std::move( dists ) );

      THEN( "the parameters can be verified" ){
        auto eip = law4.interpolationParameters();
        REQUIRE( ranges::equal( NBT, eip.NBT() ) );
        REQUIRE( ranges::equal( INT, eip.schemes() ) );
        REQUIRE( ranges::equal( energies, law4.incidentEnergies() ) );

        REQUIRE( 3 == law4.distributions().size() );
      }
    }
  } // GIVEN valid

  GIVEN( "invalid input values" ){
    WHEN( "wrong number of distributions" ){
      std::vector< Dist > dists{
        Dist{ INTT, dEnergies, PDF, CDF },
        Dist{ INTT, dEnergies, PDF, CDF },
        Dist{ INTT, dEnergies, PDF, CDF },
        Dist{ INTT, dEnergies, PDF, CDF }
      };

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( ContinuousEnergyNeutron::ContinuousTabular( 
          NBT, INT, energies, std::move( dists ) ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO
