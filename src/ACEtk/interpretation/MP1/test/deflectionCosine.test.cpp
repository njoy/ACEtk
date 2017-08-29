
#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO("test interpretation::MP1::deflectionCosine"){  
  auto table = Table( njoy::utility::slurpFileToMemory("1000.mp1") );
  
  GIVEN("An ACE Table for 1000.mp1"){
    
    const auto mp1 = interpretation::MP1( table );

    WHEN("querying for the total xs for order 1"){
      const auto mu = mp1.deflectionCosine(1) | ranges::to_vector;
      REQUIRE( mu.size() == 287 );
      
      for ( const auto& vec : mu ) {
	RANGES_FOR( const auto entry, vec ){
	  REQUIRE( entry <= 1.0 );
	  REQUIRE( entry >= -1.0 );	  
	}
      }
    }

    WHEN("querying for the total xs for order 2"){
      const auto mu = mp1.deflectionCosine(2) | ranges::to_vector;
      REQUIRE( mu.size() == 287 );
      
      for ( const auto& vec : mu ) {
	RANGES_FOR( const auto entry, vec ){
	  REQUIRE( entry <= 1.0 );
	  REQUIRE( entry >= -1.0 );	  
	}
      }
    }

    WHEN("querying for the total xs for order 4"){
      const auto mu = mp1.deflectionCosine(4) | ranges::to_vector;
      REQUIRE( mu.size() == 287 );
      
      for ( const auto& vec : mu ) {
	RANGES_FOR( const auto entry, vec ){
	  REQUIRE( entry <= 1.0 );
	  REQUIRE( entry >= -1.0 );	  
	}
      }
    }

    WHEN("querying for the total xs for order 8"){
      const auto mu = mp1.deflectionCosine(8) | ranges::to_vector;
      REQUIRE( mu.size() == 287 );
      
      for ( const auto& vec : mu ) {
	RANGES_FOR( const auto entry, vec ){
	  REQUIRE( entry <= 1.0 );
	  REQUIRE( entry >= -1.0 );	  
	}
      }
    }

    WHEN("querying for the total xs for order 16"){
      const auto mu = mp1.deflectionCosine(16) | ranges::to_vector;
      REQUIRE( mu.size() == 287 );
      
      for ( const auto& vec : mu ) {
	RANGES_FOR( const auto entry, vec ){
	  REQUIRE( entry <= 1.0 );
	  REQUIRE( entry >= -1.0 );	  
	}
      }
    }       
  }
}




