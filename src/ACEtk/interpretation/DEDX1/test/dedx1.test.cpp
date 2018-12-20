#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

SCENARIO("test interpretation::DEDX1"){

  using namespace dimwits;

  constexpr auto mev = 1.0 * mega(electronVolt);
  constexpr auto cm = 1.0 * centi(meter);
  constexpr auto g = 1.0 * gram;

  auto exp_w_units = [](auto units){
    return [units](auto&& entry){
      return std::exp(entry) * units;};
  };
  
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

    auto refLogErgFirstFour = std::vector<double>{-8.517193,-8.363688,-8.210182,-8.056676};
    auto refLogErgMiddleFour = std::vector<double>{-2.376966, -2.223461, -2.069955, -1.916449};
    auto refLogErgLastFour = std::vector<double>{4.8378, 4.991306, 5.1448120, 5.298317};
    
    WHEN("querying for the log of energies"){

      auto logEnergies = standard.logEnergies();
      REQUIRE( logEnergies.size() == 91 );

      THEN("taking the first four entries"){
	auto test = logEnergies | ranges::view::take_exactly(4) | ranges::to_vector;
	REQUIRE( test == refLogErgFirstFour );
      }

      AND_THEN("taking entries 40-43 (note that first index is 0)"){
	auto test =logEnergies | ranges::view::drop_exactly(40)
	  | ranges::view::take_exactly(4) | ranges::to_vector;

	RANGES_FOR(auto&& pair, ranges::view::zip(refLogErgMiddleFour,test)){
	  REQUIRE( pair.first == Approx(pair.second).margin(1e-15) );
	}
      }

      AND_THEN("taking the last four entries"){
	auto test = logEnergies | ranges::view::drop_exactly(87) | ranges::to_vector;
	REQUIRE( test == refLogErgLastFour );
      }            
    }
    
    WHEN("querying for the energies"){

      auto energies = standard.energies();
      REQUIRE( energies.size() == 91 );

    
      THEN("taking the first four entries"){
	auto refExp = refLogErgFirstFour | ranges::view::transform(exp_w_units(mev)) | ranges::to_vector;
	auto test = energies | ranges::view::take_exactly(4) | ranges::to_vector;
	REQUIRE( test == refExp );
      }
      
      AND_THEN("taking entries 40-43 (note that first index is 0)"){
	auto refExp = refLogErgMiddleFour | ranges::view::transform(exp_w_units(mev)) | ranges::to_vector;
	auto test = energies | ranges::view::drop_exactly(40)
	  | ranges::view::take_exactly(4) | ranges::to_vector;

	// precision weirdness
	RANGES_FOR(auto&& pair, ranges::view::zip(refExp,test)){
	  REQUIRE( pair.first.value == Approx(pair.second.value).margin(1e-15) ); 
	}
      }

      AND_THEN("taking the last four entries"){
	auto refExp = refLogErgLastFour | ranges::view::transform(exp_w_units(mev)) | ranges::to_vector;	
	auto test = energies | ranges::view::drop_exactly(87) | ranges::to_vector;
	REQUIRE( test == refExp );
      } 
    }
    
    auto refLogDenFirstFour = std::vector<double>{48.35429, 49.03653, 49.71878, 50.40103};
    auto refLogDenMiddleFour = std::vector<double>{55.17676, 55.85901, 56.54126, 57.2235};
    auto refLogDenLastFour = std::vector<double>{64.72823, 65.41047, 66.09272, 66.77497};
    
    WHEN("querying for the log of densities"){

      auto logDensities = standard.logDensities();
      REQUIRE( logDensities.size() == 28 );

      THEN("taking the first four entries"){
	auto test = logDensities | ranges::view::take_exactly(4) | ranges::to_vector;

	RANGES_FOR(auto&& pair, ranges::view::zip(refLogDenFirstFour,test)){
	  REQUIRE( pair.first == Approx(pair.second).margin(1e-15) );
	}	
      }

      AND_THEN("taking entries 10-13 (note that first index is 0)"){
	auto test =logDensities | ranges::view::drop_exactly(10)
	  | ranges::view::take_exactly(4) | ranges::to_vector;

	RANGES_FOR(auto&& pair, ranges::view::zip(refLogDenMiddleFour,test)){
	  REQUIRE( pair.first == Approx(pair.second).margin(1e-15) );
	}
      }

      AND_THEN("taking the last four entries"){
	auto test = logDensities | ranges::view::drop_exactly(24) | ranges::to_vector;

	RANGES_FOR(auto&& pair, ranges::view::zip(refLogDenLastFour, test)){
	  REQUIRE( pair.first == Approx(pair.second).margin(1e-15) );
	}	
      }
    }
    
    WHEN("querying for the densities"){

      auto densities = standard.densities();
      REQUIRE( densities.size() == 28 );

      constexpr auto gpcc = g/cm/cm/cm;
      
      THEN("taking the first four entries"){
	auto refExp = refLogDenFirstFour | ranges::view::transform(exp_w_units(gpcc)) | ranges::to_vector;
	auto test = densities | ranges::view::take_exactly(4) | ranges::to_vector;

	RANGES_FOR(auto&& pair, ranges::view::zip(refExp, test)){
	  REQUIRE( pair.first.value == Approx(pair.second.value).margin(1e-15) );
	}	
      }
      
      AND_THEN("taking entries 10-13 (note that first index is 0)"){
	auto refExp = refLogDenMiddleFour | ranges::view::transform(exp_w_units(gpcc)) | ranges::to_vector;
	auto test = densities | ranges::view::drop_exactly(10)
	  | ranges::view::take_exactly(4) | ranges::to_vector;
	
	RANGES_FOR(auto&& pair, ranges::view::zip(refExp, test)){
	  REQUIRE( pair.first.value == Approx(pair.second.value).margin(1e-15) ); 
	}
      }

      AND_THEN("taking the last four entries"){
	auto refExp = refLogDenLastFour | ranges::view::transform(exp_w_units(gpcc)) | ranges::to_vector;	
	auto test = densities | ranges::view::drop_exactly(24) | ranges::to_vector;

	RANGES_FOR(auto&& pair, ranges::view::zip(refExp, test)){
	  REQUIRE( pair.first.value == Approx(pair.second.value).margin(1e-15) ); 
	}
      } 
    }
    
    auto refLogTempFirstFour = std::vector<double>{-11.51293, -10.83068, -10.14843, -9.466183};
    auto refLogTempMiddleFour = std::vector<double>{-4.690451, -4.008204, -3.325956, -2.643709};
    auto refLogTempLastFour = std::vector<double>{4.861013, 5.54326, 6.225508, 6.907755};
    
    WHEN("querying for the log of temperatures"){

      auto logTemperatures = standard.logTemperatures();
      REQUIRE( logTemperatures.size() == 28 );

      THEN("taking the first four entries"){
	auto test = logTemperatures | ranges::view::take_exactly(4) | ranges::to_vector;

	RANGES_FOR(auto&& pair, ranges::view::zip(refLogTempFirstFour,test)){
	  REQUIRE( pair.first == Approx(pair.second).margin(1e-15) );
	}	
      }

      AND_THEN("taking entries 10-13 (note that first index is 0)"){
	auto test =logTemperatures | ranges::view::drop_exactly(10)
	  | ranges::view::take_exactly(4) | ranges::to_vector;

	RANGES_FOR(auto&& pair, ranges::view::zip(refLogTempMiddleFour,test)){
	  REQUIRE( pair.first == Approx(pair.second).margin(1e-15) );
	}
      }

      AND_THEN("taking the last four entries"){
	auto test = logTemperatures | ranges::view::drop_exactly(24) | ranges::to_vector;
	REQUIRE( test == refLogTempLastFour );
      }
    }
    
    WHEN("querying for the temperatures"){

      auto temperatures = standard.temperatures();
      REQUIRE( temperatures.size() == 28 );

      THEN("taking the first four entries"){
	auto refExp = refLogTempFirstFour | ranges::view::transform(exp_w_units(mev)) | ranges::to_vector;
	auto test = temperatures | ranges::view::take_exactly(4) | ranges::to_vector;

	RANGES_FOR(auto&& pair, ranges::view::zip(refExp, test)){
	  REQUIRE( pair.first.value == Approx(pair.second.value).margin(1e-15) );
	}	
      }
      
      AND_THEN("taking entries 10-13 (note that first index is 0)"){
	auto refExp = refLogTempMiddleFour | ranges::view::transform(exp_w_units(mev)) | ranges::to_vector;
	auto test = temperatures | ranges::view::drop_exactly(10)
	  | ranges::view::take_exactly(4) | ranges::to_vector;

	RANGES_FOR(auto&& pair, ranges::view::zip(refExp, test)){
	  REQUIRE( pair.first.value == Approx(pair.second.value).margin(1e-15) ); 
	}
      }

      AND_THEN("taking the last four entries"){
	auto refExp = refLogTempLastFour | ranges::view::transform(exp_w_units(mev)) | ranges::to_vector;	
	auto test = temperatures | ranges::view::drop_exactly(24) | ranges::to_vector;

	RANGES_FOR(auto&& pair, ranges::view::zip(refExp, test)){
	  REQUIRE( pair.first.value == Approx(pair.second.value).margin(1e-15) ); 
	}
	// REQUIRE( test == refExp ); this will not compile...
      } 
    }
  }
}
