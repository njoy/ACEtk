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
    
    WHEN("querying for the log of energies"){

      auto logEnergies = standard.logEnergies();
      REQUIRE( logEnergies.size() == 91 );

      THEN("taking the first four entries"){
	auto reference = std::vector<double>{-8.517193,-8.363688,-8.210182,-8.056676};
	auto test = logEnergies | ranges::view::take_exactly(4) | ranges::to_vector;
	REQUIRE( test == reference );
      }

      AND_THEN("taking entries 40-43 (note that first index is 0)"){
	auto reference = std::vector<double>{-2.376966, -2.223461, -2.069955, -1.916449};
	auto test =logEnergies | ranges::view::drop_exactly(40)
	  | ranges::view::take_exactly(4) | ranges::to_vector;

	// precision weirdness
	RANGES_FOR(auto&& pair, ranges::view::zip(reference,test)){
	  REQUIRE( pair.first == Approx(pair.second).margin(1e-15) );
	}
      }

      AND_THEN("taking the last four entries"){
	auto reference = std::vector<double>{4.8378, 4.991306, 5.1448120, 5.298317};
	auto test = logEnergies | ranges::view::drop_exactly(87) | ranges::to_vector;
	REQUIRE( test == reference );
      }            

    }
    
    WHEN("querying for the energies"){
      auto energies = standard.energies();
      REQUIRE( energies.size() == 91 );

      constexpr auto mev = 1.0 * dimwits::mega( dimwits::electronVolt );
      auto exp = [=](auto&& entry){
	return std::exp(entry) * mev;};
    
      THEN("taking the first four entries"){
	auto reference = std::vector<double>{-8.517193,-8.363688,-8.210182,-8.056676};
	auto refExp = reference | ranges::view::transform(exp) | ranges::to_vector;
	auto test = energies | ranges::view::take_exactly(4) | ranges::to_vector;
	REQUIRE( test == refExp );
      }
      
      AND_THEN("taking entries 40-43 (note that first index is 0)"){
	auto reference = std::vector<double>{-2.376966, -2.223461, -2.069955, -1.916449};
	auto refExp = reference | ranges::view::transform(exp) | ranges::to_vector;
	auto test = energies | ranges::view::drop_exactly(40)
	  | ranges::view::take_exactly(4) | ranges::to_vector;

	// precision weirdness
	RANGES_FOR(auto&& pair, ranges::view::zip(refExp,test)){
	  REQUIRE( pair.first.value == Approx(pair.second.value).margin(1e-15) ); 
	}
      }

      AND_THEN("taking the last four entries"){
	auto reference = std::vector<double>{4.8378, 4.991306, 5.1448120, 5.298317};
	auto refExp = reference | ranges::view::transform(exp) | ranges::to_vector;	
	auto test = energies | ranges::view::drop_exactly(87) | ranges::to_vector;
	REQUIRE( test == refExp );
      } 
    }

    WHEN("querying for the log of densities"){
      
      auto logDensities = standard.logDensities();
      REQUIRE( logDensities.size() == 28 );
      
      THEN("taking the first four entries"){
	auto reference = std::vector<double>{-11.51293, -10.83068, -10.14843,-9.466183};
	auto test = logDensities | ranges::view::take_exactly(4) | ranges::to_vector;
	//REQUIRE( test == reference );
	// precision weirdness
	RANGES_FOR(auto&& pair, ranges::view::zip(reference,test)){
	  REQUIRE( pair.first == Approx(pair.second).margin(1e-15) );
	}	
      }
      
      AND_THEN("taking entries 10-13"){
	auto reference = std::vector<double>{-4.690451, -4.008204, -3.325956, -2.643709};	
	auto test =logDensities | ranges::view::drop_exactly(10)
	  | ranges::view::take_exactly(4) | ranges::to_vector;
	//REQUIRE( test == reference );
	// precision weirdness
	RANGES_FOR(auto&& pair, ranges::view::zip(reference,test)){
	  REQUIRE( pair.first == Approx(pair.second).margin(1e-15) );
	}
      }

      AND_THEN("taking the last four entries"){
	auto reference = std::vector<double>{4.861013, 5.54326, 6.225508, 6.907755};	
	auto test = logDensities | ranges::view::drop_exactly(24) | ranges::to_vector;
	REQUIRE( test == reference );
      }            
    }
    
    WHEN("querying for the densities"){
      auto densities = standard.densities();
      REQUIRE( densities.size() == 28 );

      constexpr auto mev = 1.0 * dimwits::mega( dimwits::electronVolt );
      auto exp = [=](auto&& entry){
	return std::exp(entry) * mev;};

      THEN("taking the first four entries"){
	auto reference = std::vector<double>{-11.51293, -10.83068, -10.14843,-9.466183};
	auto refExp = reference | ranges::view::transform(exp) | ranges::to_vector;
	auto test = densities | ranges::view::take_exactly(4) | ranges::to_vector;
	// REQUIRE( test == refExp );
	// precision weirdness
	RANGES_FOR(auto&& pair, ranges::view::zip(refExp, test)){
	  REQUIRE( pair.first.value == Approx(pair.second.value).margin(1e-15) );
	}	
      }
    
      AND_THEN("taking entries 10-13 (note that first index is 0)"){
	auto reference = std::vector<double>{-4.690451, -4.008204, -3.325956, -2.643709};
	auto refExp = reference | ranges::view::transform(exp) | ranges::to_vector;
	auto test = densities | ranges::view::drop_exactly(10)
	  | ranges::view::take_exactly(4) | ranges::to_vector;
	// REQUIRE( test == refExp );
	// precision weirdness
	RANGES_FOR(auto&& pair, ranges::view::zip(refExp,test)){
	  REQUIRE( pair.first.value == Approx(pair.second.value).margin(1e-15) ); 
	}
      }
      
      AND_THEN("taking the last four entries"){
	auto reference = std::vector<double>{4.861013, 5.54326, 6.225508, 6.907755};
	auto refExp = reference | ranges::view::transform(exp) | ranges::to_vector;	
	auto test = densities | ranges::view::drop_exactly(24) | ranges::to_vector;
	REQUIRE( test == refExp );
      } 
    }
  }
  
}
