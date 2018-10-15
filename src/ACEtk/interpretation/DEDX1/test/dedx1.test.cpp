#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

SCENARIO("test interpretation::DEDX1"){  

  auto table = njoy::ACEtk::Table( njoy::utility::slurpFileToMemory("1001.dedx.h1") );
  const auto dedx1 = njoy::ACEtk::interpretation::DEDX1( std::move(table) );
  
  GIVEN("a dedx1 interpretation"){

    WHEN("querying for the target atomic number"){
      REQUIRE( dedx1.atomicNumber() == 1 );
    }

    WHEN("querying for the energy spacing"){
      REQUIRE( dedx1.energySpacing() == 1 );
    }

    WHEN("querying for the density spacing"){
      REQUIRE( dedx1.densitySpacing() == 1 );
    }

    WHEN("querying for the temperature spacing"){
      REQUIRE( dedx1.temperatureSpacing() == 1 );
    }        
    
  }
  
}
