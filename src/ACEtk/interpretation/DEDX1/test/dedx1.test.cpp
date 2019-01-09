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

  auto make_approx = [](auto tol){
    return ranges::view::repeat_n(Approx(0.0).margin(tol), 4);
  };
  
  auto rel_diff = [](auto&& first, auto&& second){
    return (first-second)/first; 
  };
  
  GIVEN("A faux stopping power data table"){
    auto table = njoy::ACEtk::Table(njoy::utility::slurpFileToMemory("faux.dedx.data"));
    const auto faux = njoy::ACEtk::interpretation::DEDX1(std::move(table));
    
    WHEN("querying for the target atomic number"){
      REQUIRE( faux.atomicNumber() == 1 );
    }

    WHEN("querying for the energy spacing"){
      REQUIRE( faux.energySpacing() == 0.0 );
    }

    WHEN("querying for the density spacing"){
      REQUIRE( faux.densitySpacing() == 0.0 );
    }

    WHEN("querying for the temperature spacing"){
      REQUIRE( faux.temperatureSpacing() == 0.0 );
    }

    WHEN("querying for standard stopping power model without a cutoff"){
      const auto standard = faux.standardWithoutCutoff();      
      auto sp = standard.stoppingPowers();
      auto base = std::vector<double>(2,0.0);
      double i = 0.0;
      auto increment = [&](auto&& val){return val+i;};	

      AND_THEN("iterating through the stopping power values and "
	       "querying for the values"){

	RANGES_FOR(auto&& entry, sp){
	  auto reference = base | ranges::view::transform(increment);
	  REQUIRE( ranges::equal(entry.logValues(), reference) );
	  ++i;
	}
      }
      
      AND_THEN("constraining on density"){
	i = 0;
	RANGES_FOR(auto&& entry, sp.floor(2.2/cc)){
	  auto reference = base | ranges::view::transform(increment);
	  REQUIRE( ranges::equal(entry.logValues(), reference) );
	  i+=3;
	}
	
	i = 1;
	RANGES_FOR(auto&& entry, sp.ceil(2.2/cc)){
	  auto reference = base | ranges::view::transform(increment);
	  REQUIRE( ranges::equal(entry.logValues(), reference) );
	  i+=3;
	}	  	  
      }
      
      AND_THEN("constraining on temperature"){
	i = 6;
	RANGES_FOR(auto&& entry, sp.ceil(150.0*mev)){
	  auto reference = base | ranges::view::transform(increment);
	  REQUIRE( ranges::equal(entry.logValues(), reference) );
	  ++i;
	}
	
	i = 3;
	RANGES_FOR(auto&& entry, sp.floor(150.0*mev)){
	  auto reference = base | ranges::view::transform(increment);
	  REQUIRE( ranges::equal(entry.logValues(), reference) );
	  ++i;
	}
      }
      /*
      AND_THEN("constraining on density and temperature"){
	auto ff = sp.floor(2.2/cc).floor(150.0*mev);
	// auto reference = std::vector<double>{4.0, 4.0};
	// REQUIRE( ranges::equal(ff.logValues(), reference) );
      }
      */
    }
  }
  
  auto table =
    njoy::ACEtk::Table(njoy::utility::slurpFileToMemory("1001.dedx.h1"));
  const auto dedx1 = njoy::ACEtk::interpretation::DEDX1(std::move(table));      
  GIVEN("a DEDX1 interpretation with real data"){

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
    auto s0 = standard.stoppingPowers();

      WHEN("Querying via the parameterized interface"){

      auto hh = s0.ceil( 1.5 * mev ).ceil( 1.5e24 / cc );
      REQUIRE( hh.logDensity_ == 55.85901 );
      REQUIRE( hh.logTemperature_ ==  0.7675284);

      hh = s0.ceil( 1.5e24 / cc ).ceil( 1.5 * mev );
      REQUIRE( hh.logDensity_ == 55.85901 );
      REQUIRE( hh.logTemperature_ ==  0.7675284);  
    
      auto hl = s0.ceil( 1.5 * mev ).floor( 1.5e24 / cc );
      REQUIRE( hl.logDensity_ == Approx(55.17676).epsilon(1e-15) );
      REQUIRE( hl.logTemperature_ ==  0.7675284);
    
      hl = s0.floor( 1.5e24 / cc ).ceil( 1.5 * mev );
      REQUIRE( hl.logDensity_ == Approx(55.17676).epsilon(1e-15) );
      REQUIRE( hl.logTemperature_ ==  0.7675284);  
    
      auto ll = s0.floor( 1.5 * mev ).floor( 1.5e24 / cc );
      REQUIRE( ll.logDensity_ == Approx(55.17676).epsilon(1e-15) );
      REQUIRE( ll.logTemperature_ ==  0.08528093);
    
      ll = s0.floor( 1.5e24 / cc ).floor( 1.5 * mev );  
      REQUIRE( ll.logDensity_ == Approx(55.17676).epsilon(1e-15) );
      REQUIRE( ll.logTemperature_ ==  0.08528093);
    
      auto lh = s0.floor( 1.5 * mev ).ceil( 1.5e24 / cc );
      REQUIRE( lh.logDensity_ == 55.85901 );  
      REQUIRE( lh.logTemperature_ ==  0.08528093);  
    
      lh = s0.ceil( 1.5e24 / cc ).floor( 1.5 * mev );
      REQUIRE( lh.logDensity_ == 55.85901 );  
      REQUIRE( lh.logTemperature_ ==  0.08528093);
    }
  
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
	auto test = logEnergies | ranges::view::drop_exactly(40)
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
  }
}
