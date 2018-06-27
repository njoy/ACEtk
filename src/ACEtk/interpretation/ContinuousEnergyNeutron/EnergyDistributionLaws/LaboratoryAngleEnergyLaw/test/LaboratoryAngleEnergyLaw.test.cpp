#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

using angDist = ContinuousEnergyNeutron::Law67::AngularDistribution;
using Dist = ContinuousEnergyNeutron::SecondaryDistribution;

// std::vector< angDist > makeAngularDistributions( int n ){
//   std::vector< angDist > dists;
//   std::vector< double > energies{ 5.0, 3.0, 8.0 };

//   int INTMU{ 2 };
//   int INTEP{ 3 };
//   for( int i=0; i<n; ++i ){
//     std::vector< double > dEnergies{ 10.0, 11.0, 12.0 };
//     std::vector< double > PDF{ 0.2, 0.5, 0.3 };
//     std::vector< double > CDF{ 0.2, 0.7, 1.0 };

//     std::vector< ContinuousEnergyNeutron::SecondaryDistribution > dists{
//       Dist{ INTEP, dEnergies, PDF, CDF },
//       Dist{ INTEP, dEnergies, PDF, CDF },
//       Dist{ INTEP, dEnergies, PDF, CDF }
//     };

//     dists.push_back( angDist{ INTMU, energies, std::move( dists ) } );
//   }

//   return dists;
// }

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
    angDist{ INTMU, energies, std::move( dists ) },
    angDist{ INTMU, energies, std::move( dists ) },
    angDist{ INTMU, energies, std::move( dists ) }
  };

  // auto angDists = makeAngularDistributions( 3 );
  GIVEN( "valid inputs" ){
    WHEN( "constructing a LAW67" ){
      ContinuousEnergyNeutron::LaboratoryAngleEnergyLaw law67{
          NBT, INT, energies, std::move( angDists ) };

      THEN( "the parameters can be verified" ){
        auto eip = law67.interpolationParameters();
        REQUIRE( ranges::equal( NBT, eip.NBT() ) );
        REQUIRE( ranges::equal( INT, eip.schemes() ) );
        REQUIRE( ranges::equal( energies, law67.incidentEnergies() ) );

      }
    }
  } // GIVEN valid

  GIVEN( "invalid inputs" ){
  } // GIVEN invalid
} // SCENARIO
