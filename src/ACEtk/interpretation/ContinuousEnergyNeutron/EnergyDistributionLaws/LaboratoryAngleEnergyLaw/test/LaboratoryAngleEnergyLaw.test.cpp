#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

template< typename T >
auto copy( T&& t ){
  return t;
}

using namespace njoy::ACEtk::interpretation;
using namespace dimwits;

using angDist = ContinuousEnergyNeutron::Law67::AngularDistribution;
using Dist = ContinuousEnergyNeutron::SecondaryDistribution;

SCENARIO( "Law67" ){
  std::vector< double > NBT{ 1, 3 };
  std::vector< double > INT{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 3.0 };

  int INTEP{ 3 };
  std::vector< double > dEnergies{ 10.0, 11.0, 12.0 };
  std::vector< double > PDF{ 0.2, 0.5, 0.3 };
  std::vector< double > CDF{ 0.2, 0.7, 1.0 };
  
  std::vector< Dist > dists{
    Dist{ INTEP, dEnergies, PDF, CDF },
    Dist{ INTEP, dEnergies, PDF, CDF },
    Dist{ INTEP, dEnergies, PDF, CDF }
  };

  int INTMU{ 2 };
  std::vector< angDist > angDists{
    angDist{ INTMU, energies, copy( dists ) },
    angDist{ INTMU, energies, copy( dists ) },
    angDist{ INTMU, energies, copy( dists ) }
  };

  GIVEN( "valid inputs" ){
    WHEN( "constructing a LAW67" ){
      ContinuousEnergyNeutron::LaboratoryAngleEnergyLaw law67{
          NBT, INT, energies, std::move( angDists ) };

      THEN( "the parameters can be verified" ){
        auto eip = law67.interpolationParameters();
        REQUIRE( ranges::equal( NBT, eip.NBT() ) );
        REQUIRE( ranges::equal( INT, eip.schemes() ) );

        auto refEnergies = scaleBy( 1.0*mega( electronVolts ) )( energies );
        REQUIRE( ranges::equal( refEnergies, law67.incidentEnergies() ) );

        REQUIRE( 3 == law67.angularDistributions().size() );
        REQUIRE( 3 == law67.NMU() );
      }
    }
  } // GIVEN valid

  GIVEN( "invalid inputs" ){
    WHEN( "wrong number of angular distributions" ){
      std::vector< angDist > angDists{
        angDist{ INTMU, energies, copy( dists ) },
        angDist{ INTMU, energies, copy( dists ) },
        angDist{ INTMU, energies, copy( dists ) },
        angDist{ INTMU, energies, copy( dists ) }
      };

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( ContinuousEnergyNeutron::LaboratoryAngleEnergyLaw(
            NBT, INT, energies, std::move( angDists ) ) );
      }
    }
  } // GIVEN invalid
} // SCENARIO
