#include "catch.hpp"
#include "ACEtk.hpp"

SCENARIO("test interpretation::DEDX1::StandardWithoutCutoff"){  

  using namespace dimwits;
  
  auto mev = 1.0 * mega(electronVolt);
  auto cm = 1.0 * centi(meter);
  auto g = 1.0 * gram;  
  
  auto table = njoy::ACEtk::Table(njoy::utility::slurpFileToMemory("1001.dedx.h1"));
  const auto dedx1 = njoy::ACEtk::interpretation::DEDX1(std::move(table));
  
  GIVEN("a DEDX1 interpretation"){

    WHEN("querying for log of the stopping power values"){
      auto logStopping = dedx1.standardWithoutCutoff().logStoppingPowers();
    }

    WHEN("querying for log of the stopping power values"){
      auto logStopping = dedx1.standardWithoutCutoff().stoppingPowers();
    }
    
  }
  
}
