
#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO("test interpretation::MP1::DiscreteData::deflectionCosines"){  
  auto table = Table( njoy::utility::slurpFileToMemory("1000.mp1") );
  
  GIVEN("An ACE Table for 1000.mp1"){
    
    const auto mp1 = interpretation::MP1( table );

    WHEN("querying for the target atomic number"){
      REQUIRE( mp1.atomicNumber() == 1 );
    }
    
    WHEN("querying for the total xs for order 1"){
      const auto mu = mp1.discreteData( 1 ).deflectionCosines( ) | ranges::to_vector;
      REQUIRE( mu.size() == 287 );
      
      for ( const auto& vec : mu ) {
	RANGES_FOR( const auto entry, vec ){
	  REQUIRE( entry <= 1.0 );
	  REQUIRE( entry >= -1.0 );	  
	}
      }
    }

    WHEN("querying for the total xs for order 2"){
      const auto mu = mp1.discreteData( 2 ).deflectionCosines( ) | ranges::to_vector;      
      REQUIRE( mu.size() == 287 );
      
      for ( const auto& vec : mu ) {
	RANGES_FOR( const auto entry, vec ){
	  REQUIRE( entry <= 1.0 );
	  REQUIRE( entry >= -1.0 );	  
	}
      }
    }

    WHEN("querying for the total xs for order 4"){
      const auto mu = mp1.discreteData( 4 ).deflectionCosines( ) | ranges::to_vector;            
      REQUIRE( mu.size() == 287 );
      
      for ( const auto& vec : mu ) {
	RANGES_FOR( const auto entry, vec ){
	  REQUIRE( entry <= 1.0 );
	  REQUIRE( entry >= -1.0 );	  
	}
      }
    }

    WHEN("querying for the total xs for order 8"){
      const auto mu = mp1.discreteData( 8 ).deflectionCosines( ) | ranges::to_vector;            
      REQUIRE( mu.size() == 287 );
      
      for ( const auto& vec : mu ) {
	RANGES_FOR( const auto entry, vec ){
	  REQUIRE( entry <= 1.0 );
	  REQUIRE( entry >= -1.0 );	  
	}
      }
    }

    WHEN("querying for the total xs for order 16"){
      const auto mu = mp1.discreteData( 16 ).deflectionCosines( ) | ranges::to_vector;            
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




