#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

SCENARIO("test interpretation::DEDX1"){
  
  using namespace dimwits;

  constexpr auto mev = mega(electronVolt);
  constexpr auto cm = centi(meter);
  constexpr auto cc = cm*cm*cm;  

  auto exp_w_units = [](auto units){
    return [units](auto&& entry){
      return std::exp(entry) * units;};
  };
  
  auto make_approx = [](auto tol){return ranges::view::repeat_n(Approx(0.0).margin(tol), 4);};
  auto rel_diff = [](auto&& first, auto&& second){return (first-second)/first;};  
  
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
	auto test = logEnergies | ranges::view::take_exactly(4);
	REQUIRE( ranges::equal(test, refLogErgFirstFour) );
      }

      AND_THEN("taking entries 40-43"){
	auto test =logEnergies | ranges::view::drop_exactly(40)
	  | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refLogErgMiddleFour, test);
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}
      }

      AND_THEN("taking the last four entries"){
	auto test = logEnergies | ranges::view::drop_exactly(87);
	REQUIRE( ranges::equal(test, refLogErgLastFour) );
      }            
    }
    
    WHEN("querying for the energies"){

      auto energies = standard.energies();
      REQUIRE( energies.size() == 91 );

      THEN("taking the first four entries"){
	auto refExp = refLogErgFirstFour | ranges::view::transform(exp_w_units(mev));
	auto test = energies | ranges::view::take_exactly(4);
	REQUIRE( ranges::equal(test, refExp) );	
      }
      
      AND_THEN("taking entries 40-43"){
	auto refExp = refLogErgMiddleFour | ranges::view::transform(exp_w_units(mev));
	auto test = energies | ranges::view::drop_exactly(40) | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refExp, test)
	  | ranges::view::transform([](auto&& x){return x.value;});
	RANGES_FOR(auto&& pair, ranges::view::zip(difference,make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}
      }

      AND_THEN("taking the last four entries"){
	auto refExp = refLogErgLastFour | ranges::view::transform(exp_w_units(mev));
	auto test = energies | ranges::view::drop_exactly(87);
	REQUIRE( ranges::equal(test, refExp) );
      } 
    }
    
    auto refLogDenFirstFour = std::vector<double>{48.35429, 49.03653, 49.71878, 50.40103};
    auto refLogDenMiddleFour = std::vector<double>{55.17676, 55.85901, 56.54126, 57.2235};
    auto refLogDenLastFour = std::vector<double>{64.72823, 65.41047, 66.09272, 66.77497};

    WHEN("querying for the log of densities"){

      auto logDensities = standard.logDensities();
      REQUIRE( logDensities.size() == 28 );

      THEN("taking the first four entries"){
	auto test = logDensities | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refLogDenFirstFour, test);
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}	
      }

      AND_THEN("taking entries 10-13"){
	auto test = logDensities | ranges::view::drop_exactly(10)
	  | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refLogDenMiddleFour, test);
	RANGES_FOR(auto&& pair, ranges::view::zip(difference,make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}
      }

      AND_THEN("taking the last four entries"){
	auto test = logDensities | ranges::view::drop_exactly(24);
	auto difference = ranges::view::zip_with(rel_diff, refLogDenLastFour, test);
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}	
      }            
    }
    
    WHEN("querying for the densities"){

      auto densities = standard.densities();
      REQUIRE( densities.size() == 28 );
      auto cc = cm*cm*cm;
      THEN("taking the first four entries"){
	auto refExp = refLogDenFirstFour | ranges::view::transform(exp_w_units(1/cc));
	auto test = densities | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refExp, test)
	  | ranges::view::transform([](auto&& x){return x.value;});
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}		
      }
      
      AND_THEN("taking entries 10-13"){
	auto refExp = refLogDenMiddleFour | ranges::view::transform(exp_w_units(1/cc));
	auto test = densities | ranges::view::drop_exactly(10) | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refExp, test)
	  | ranges::view::transform([](auto&& x){return x.value;});
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}
      }

      AND_THEN("taking the last four entries"){
	auto refExp = refLogDenLastFour | ranges::view::transform(exp_w_units(1/cc));
	auto test = densities | ranges::view::drop_exactly(24);
	auto difference = ranges::view::zip_with(rel_diff, refExp, test)
	  | ranges::view::transform([](auto&& x){return x.value;});
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
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
	auto test = logTemperatures | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refLogTempFirstFour, test);
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}	
      }

      AND_THEN("taking entries 10-13"){
	auto test = logTemperatures | ranges::view::drop_exactly(10)
	  | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refLogTempMiddleFour, test);
	RANGES_FOR(auto&& pair, ranges::view::zip(difference,make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}
      }

      AND_THEN("taking the last four entries"){
	auto test = logTemperatures | ranges::view::drop_exactly(24);
	auto difference = ranges::view::zip_with(rel_diff, refLogTempLastFour, test);
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}	
      }            
    }
    
    WHEN("querying for the temperatures"){

      auto temperatures = standard.temperatures();
      REQUIRE( temperatures.size() == 28 );
     
      THEN("taking the first four entries"){
	auto refExp = refLogTempFirstFour | ranges::view::transform(exp_w_units(mev));
	auto test = temperatures | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refExp, test)
	  | ranges::view::transform([](auto&& x){return x.value;});
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}		
      }
      
      AND_THEN("taking entries 10-13"){
	auto refExp = refLogTempMiddleFour | ranges::view::transform(exp_w_units(mev));
	auto test = temperatures | ranges::view::drop_exactly(10) | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refExp, test)
	  | ranges::view::transform([](auto&& x){return x.value;});
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}
      }

      AND_THEN("taking the last four entries"){
	auto refExp = refLogTempLastFour | ranges::view::transform(exp_w_units(mev));
	auto test = temperatures | ranges::view::drop_exactly(24);
	auto difference = ranges::view::zip_with(rel_diff, refExp, test)
	  | ranges::view::transform([](auto&& x){return x.value;});
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}	
      } 
    }

    auto refLogSPFirstFour = std::vector<double>{-48.6146, -48.64614, -48.69095, -48.74642};
    auto refLogSPMiddleFour = std::vector<double>{-47.82199, -47.80323, -47.82374, -47.87637};
    auto refLogSPLastFour = std::vector<double>{-60.42358, -60.57709, -60.73059, -60.8841};

    WHEN("querying for the log of stoppingPowers"){

      auto logStoppingPowers = standard.logStoppingPowers();
      REQUIRE( logStoppingPowers.size() == 71344 );

      THEN("taking the first four entries"){
	auto test = logStoppingPowers | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refLogSPFirstFour, test);
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}	
      }

      AND_THEN("taking middle entries"){
	auto test = logStoppingPowers | ranges::view::drop_exactly(35675)
	  | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refLogSPMiddleFour, test);
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}
      }

      AND_THEN("taking the last four entries"){
	auto test = logStoppingPowers | ranges::view::drop_exactly(71340);
	auto difference = ranges::view::zip_with(rel_diff, refLogSPLastFour, test);
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}	
      }            
    }
    
    WHEN("querying for the stoppingPowers"){

      auto stoppingPowers = standard.stoppingPowers();
      REQUIRE( stoppingPowers.size() == 71344 );
     
      THEN("taking the first four entries"){
	auto refExp = refLogSPFirstFour | ranges::view::transform(exp_w_units(cm*cm*mev));
	auto test = stoppingPowers | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refExp, test)
	  | ranges::view::transform([](auto&& x){return x.value;});
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}		
      }
      
      AND_THEN("taking middle entries"){
	auto refExp = refLogSPMiddleFour | ranges::view::transform(exp_w_units(cm*cm*mev));
	auto test = stoppingPowers | ranges::view::drop_exactly(35675) | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refExp, test)
	  | ranges::view::transform([](auto&& x){return x.value;});
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}
      }

      AND_THEN("taking the last four entries"){
	auto refExp = refLogSPLastFour | ranges::view::transform(exp_w_units(cm*cm*mev));
	auto test = stoppingPowers | ranges::view::drop_exactly(71340);
	auto difference = ranges::view::zip_with(rel_diff, refExp, test)
	  | ranges::view::transform([](auto&& x){return x.value;});
	RANGES_FOR(auto&& pair, ranges::view::zip(difference, make_approx(1e-15))){
	  REQUIRE( pair.first == pair.second );
	}	
      } 
    }

    WHEN("querying for the stoppingPowers at density = 1e21/cc "
	 "and temperature = 1e-5 MeV (kT)"){

      //      auto logStoppingPowers = standard.logStoppingPowers( 1e21/cc, 1e-5*mev);      
      auto stoppingPowers = standard.stoppingPowers( 1.01e21/cc, 1e-5*mev);
      REQUIRE( stoppingPowers.size() == 91 );
      
      THEN("taking the first four entries"){
	auto refExp = refLogSPFirstFour | ranges::view::transform(exp_w_units(cm*cm*mev));
	auto test = stoppingPowers | ranges::view::take_exactly(4);
	auto difference = ranges::view::zip_with(rel_diff, refExp, test)
	  | ranges::view::transform([](auto&& x){return x.value;});
	
	RANGES_FOR(auto&& val, difference){
	  REQUIRE( abs(val) < 1e-14 );
	}

      }       
    }
    
  }
}
