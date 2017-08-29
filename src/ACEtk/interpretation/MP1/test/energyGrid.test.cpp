#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;


SCENARIO("test interpretation::MP1::energyGrid method"){  
  auto table = Table( njoy::utility::slurpFileToMemory("1000.mp1") );
  
  GIVEN("An ACE Table for 1000.mp1"){
    
    const auto mp1 = interpretation::MP1( table );
    auto energyGrid = mp1.energyGrid() | ranges::to_vector;
    REQUIRE( energyGrid.size() == 287 );
    auto minMaxEl = std::minmax_element( std::begin(energyGrid),
					 std::end(energyGrid) );
    
  }
}
