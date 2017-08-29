#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

namespace{
  template< typename T >
  void typeof( T ){
    puts( __PRETTY_FUNCTION__ );
  }
}
SCENARIO("test interpretation::MP1::DiscreteScatteringData"){  
  auto table = Table( njoy::utility::slurpFileToMemory("1000.mp1") );
  
  GIVEN("An ACE Table for 1000.mp1"){
    
    const auto mp1 = interpretation::MP1( table );
    const auto discreteData = mp1.discreteScatteringData( );

    WHEN("fetching single angle discrete data,"
	 "perform some basic data testing") {
      
      const auto data = discreteData.values( 1 ) | ranges::to_vector;
      REQUIRE( ( data | ranges::to_vector ).size() == 287 );

      for ( const auto tup : data ) {

	auto points = std::get<1>(tup);

	for ( size_t i=0; i<points.size(); ++i ){
	  REQUIRE( points[i] <= 1.0 );
	  REQUIRE( points[i] >= -1.0 );
	}
	
	auto cdf = std::get<2>(tup);	
	for ( size_t i=0; i<points.size(); ++i ){	  
	  REQUIRE( cdf[i] <= 1.0 );
	  REQUIRE( cdf[i] >= 0.0 );	
	}
      }

    }
    
    WHEN("fetching two angle discrete data,"
	 "perform some basic data testing") {

      const auto data = discreteData.values( 2 ) | ranges::to_vector;
      REQUIRE( ( data | ranges::to_vector ).size() == 287 );
      
      for ( const auto tup : data ) {
	
	auto points = std::get<1>(tup);
	
	for ( size_t i=0; i<points.size(); ++i ){
	  REQUIRE( points[i] <= 1.0 );
	  REQUIRE( points[i] >= -1.0 );
	}
	
	auto cdf = std::get<2>(tup);	
	for ( size_t i=0; i<points.size(); ++i ){	  
	  REQUIRE( cdf[i] <= 1.0 );
	  REQUIRE( cdf[i] >= 0.0 );	
	}
      }
    }
      
    WHEN("fetching eight angle discrete data,"
	 "perform some basic data testing") {
      
      const auto data = discreteData.values( 16 ) | ranges::to_vector;
      REQUIRE( ( data | ranges::to_vector ).size() == 287 );
      
      for ( const auto tup : data ) {
	
	auto points = std::get<1>(tup);
	
	for ( size_t i=0; i<points.size(); ++i ){
	  REQUIRE( points[i] <= 1.0 );
	  REQUIRE( points[i] >= -1.0 );
	}
	
	auto cdf = std::get<2>(tup);	
	for ( size_t i=0; i<points.size(); ++i ){	  
	  REQUIRE( cdf[i] <= 1.0 );
	  REQUIRE( cdf[i] >= 0.0 );	
	}
      }
    }
    
  }
}//
