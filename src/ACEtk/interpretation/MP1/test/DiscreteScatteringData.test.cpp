#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO("test interpretation::MP1::DiscreteScatteringData"){  
  auto table = Table( njoy::utility::slurpFileToMemory("1000.mp1") );
  
  GIVEN("An ACE Table for 1000.mp1"){
    
    const auto mp1 = interpretation::MP1( table );
    const auto data = mp1.discreteScatteringData( );

    WHEN("fetching single angle discrete data,"
	 "perform some basic data testing") {
      
      const auto oneAngleData = data.values(1) | ranges::to_vector;
      REQUIRE( oneAngleData.size() == 287 );

      for ( const auto& pair : oneAngleData ) {
	auto angle = pair.first;
	REQUIRE( angle <= 1.0 ); REQUIRE( angle >= -1.0 );

	auto cdf = pair.second;
	REQUIRE( cdf <= 1.0 ); REQUIRE( cdf >= 0.0 );	
      }
    }
      
    WHEN("fetching two angle discrete data,"
	 "perform some basic data testing") {
      
      const auto twoAngleData = data.values(1) | ranges::to_vector;
      REQUIRE( twoAngleData.size() == 287 );

      for ( const auto& pair : twoAngleData ) {
	auto angle = pair.first;
	REQUIRE( angle <= 1.0 ); REQUIRE( angle >= -1.0 );

	auto cdf = pair.second;
	REQUIRE( cdf <= 1.0 ); REQUIRE( cdf >= 0.0 );	
      }
    }
      
    WHEN("fetching eight angle discrete data,"
	 "perform some basic data testing") {
      
      const auto eightAngleData = data.values(1) | ranges::to_vector;
      REQUIRE( eightAngleData.size() == 287 );

      for ( const auto& pair : eightAngleData ) {
	auto angle = pair.first;
	REQUIRE( angle <= 1.0 ); REQUIRE( angle >= -1.0 );

	auto cdf = pair.second;
	REQUIRE( cdf <= 1.0 ); REQUIRE( cdf >= 0.0 );	
      }      
    }
    
  }
}
