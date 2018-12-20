#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

SCENARIO("test interpretation::DEDX1"){

  using namespace dimwits;

  auto mev = 1.0 * mega(electronVolt);
  auto cm = 1.0 * centi(meter);
  auto g = 1.0 * gram;
  
  auto table = njoy::ACEtk::Table(njoy::utility::slurpFileToMemory("1001.dedx.h1"));
  const auto dedx1 = njoy::ACEtk::interpretation::DEDX1(std::move(table));
  
  GIVEN("a DEDX1 interpretation"){

    WHEN("querying for the target atomic number"){
      REQUIRE( dedx1.atomicNumber() == 1 );
    }

    WHEN("querying for the energy spacing"){
      REQUIRE( dedx1.energySpacing() == 6.514417 );
    }

    WHEN("querying for the density spacing"){
      REQUIRE( dedx1.densitySpacing() == 1.465744 );
    }

    WHEN("querying for the temperature spacing"){
      REQUIRE( dedx1.temperatureSpacing() == 1.465744 );
    }
    
  }

  auto standard = dedx1.standardWithoutCutoff();

  GIVEN("a standard model without a cutoff"){
    
    WHEN("querying for the log of the energies"){
      auto logEnergies = standard.logEnergies();
      REQUIRE( logEnergies.size() == 91 );
    }
    
    WHEN("querying for the energies"){
      auto energies = standard.energies();
      REQUIRE( energies.size() == 91 );
    }
    
    WHEN("querying for the log of the densities"){
      auto logDensities = standard.logDensities();
      REQUIRE( logDensities.size() == 28 );
    }
    
    WHEN("querying for the densities"){
      auto densities = standard.densities();
      REQUIRE( densities.size() == 28 );
    }
    
    WHEN("querying for the log of the temperatures"){
      auto logTemperatures = standard.logTemperatures();
      REQUIRE( logTemperatures.size() == 28 );                  
    }
    
    WHEN("querying for the temperatures"){
      auto temperatures = standard.temperatures();
      REQUIRE( temperatures.size() == 28 );      
    }
    
  }
  
}
