#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk::interpretation;

njoy::ACEtk::Table ACETable( njoy::utility::slurpFileToMemory("92235.710nc") );

SCENARIO( "Testing interpretation:ContinuousEnergyNeutron" ){
  GIVEN( "An ACE Table for 92235.710nc" ){
    WHEN( "constructing a ContinuousEnergyNeutron interpretation" ){

      const auto ncTable = ContinuousEnergyNeutron( ACETable );

      THEN( "parameters can be extracted" ){

        REQUIRE( 92235 == ncTable.ZA() );
      }
      THEN( "the reaction IDs can be extracted and verified" ){
        std::vector<int> refNeutronIDs{{
          16, 17, 18, 37, 51, 52, 53, 54, 55, 56, 57, 58, 59, 
          60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 
          73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 
          86, 87, 88, 89, 90, 91, 102, 444}};
        std::vector<int> refPhotonIDs{{
          4001, 4002, 4003, 4004, 4005, 4006, 4007, 4008, 4009, 
          4010, 4011, 4012, 4013, 4014, 4015, 4016, 4017, 4018, 
          4019, 4020, 4021, 4022, 4023, 4024, 4025, 4026, 4027, 
          4028, 4029, 4030, 18001, 102001, 3001}};
        for( const auto tuple : ranges::view::zip( 
           refNeutronIDs, 
           ncTable.neutronReactionIDs(),
           ContinuousEnergyNeutron::neutronReactionIDs( ACETable ))
        ){
          auto ref = std::get< 0 >( tuple );
          REQUIRE( ref == Approx( std::get< 1 >( tuple ) ) );
          REQUIRE( ref == Approx( std::get< 2 >( tuple ) ) );
        }
        for( const auto tuple : ranges::view::zip( 
           refPhotonIDs, 
           ncTable.photonProductionReactionIDs(),
           ContinuousEnergyNeutron::photonProductionReactionIDs( ACETable )
              )
        ){
          auto ref = std::get< 0 >( tuple );
          REQUIRE( ref == Approx( std::get< 1 >( tuple ) ) );
          REQUIRE( ref == Approx( std::get< 2 >( tuple ) ) );
        }
      }
    }
  }
}
