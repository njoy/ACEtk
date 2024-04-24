#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO("test interpretation::MP1::totalCrossSection"){  
  auto table = Table( njoy::utility::slurpFileToMemory("1000.mp1") );
  
  GIVEN("An ACE Table for 1000.mp1"){

    const auto mp1 = interpretation::MP1( table );    

    WHEN("querying for the discrete data for order 3"){
      REQUIRE_THROWS( mp1.discreteData( 3 ).totalCrossSection( ) );
    }
    
    WHEN("querying for the total xs for order 1"){
      const auto txs =
	mp1.discreteData( 1 ).totalCrossSection( ) | ranges::to_vector;
      REQUIRE( txs.size() == 287 );
      
      auto prev = 1.0 * centi( meter ) * centi( meter );    
      for ( const auto val : txs ) {      
	REQUIRE( val <= 1e-16 * centi( meter ) * centi( meter ) );
	REQUIRE( val >= 0.0 * centi( meter ) * centi( meter ) );
	REQUIRE( prev > val );
	prev = val;
      }
      
    }

    WHEN("querying for the total xs for order 2"){
      const auto txs =
	mp1.discreteData( 2 ).totalCrossSection( ) | ranges::to_vector;
      REQUIRE( txs.size() == 287 );
      
      auto prev = 1.0 * centi( meter ) * centi( meter );    
      for ( const auto val : txs ) {      
	REQUIRE( val <= 1e-16 * centi( meter ) * centi( meter ) );
	REQUIRE( val >= 0.0 * centi( meter ) * centi( meter ) );
	REQUIRE( prev > val );
	prev = val;
      }
      
    }

    WHEN("querying for the total xs for order 4"){
      const auto txs =
	mp1.discreteData( 4 ).totalCrossSection( ) | ranges::to_vector;      
      REQUIRE( txs.size() == 287 );
      
      auto prev = 1.0 * centi( meter ) * centi( meter );    
      for ( const auto val : txs ) {      
	REQUIRE( val <= 1e-16 * centi( meter ) * centi( meter ) );
	REQUIRE( val >= 0.0 * centi( meter ) * centi( meter ) );
	REQUIRE( prev > val );
	prev = val;
      }
      
    }    

    WHEN("querying for the total xs for order 8"){
      const auto txs =
	mp1.discreteData( 8 ).totalCrossSection( ) | ranges::to_vector;      
      REQUIRE( txs.size() == 287 );
      
      auto prev = 1.0 * centi( meter ) * centi( meter );    
      for ( const auto val : txs ) {      
	REQUIRE( val <= 1e-16 * centi( meter ) * centi( meter ) );
	REQUIRE( val >= 0.0 * centi( meter ) * centi( meter ) );
	REQUIRE( prev > val );
	prev = val;
      }
      
    }
    
    WHEN("querying for the total xs for order 16"){
      const auto txs =
	mp1.discreteData( 16 ).totalCrossSection( ) | ranges::to_vector;      
      REQUIRE( txs.size() == 287 );
      
      auto prev = 1.0 * centi( meter ) * centi( meter );    
      for ( const auto val : txs ) {      
	REQUIRE( val <= 1e-16 * centi( meter ) * centi( meter ) );
	REQUIRE( val >= 0.0 * centi( meter ) * centi( meter ) );
	REQUIRE( prev > val );
	prev = val;
      }
      
    }    
    
  }
}




