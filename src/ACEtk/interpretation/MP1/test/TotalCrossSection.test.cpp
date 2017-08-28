#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

SCENARIO("test interpretation::MP1::TotalCrossSection"){  
  auto table = Table( njoy::utility::slurpFileToMemory("1000.mp1") );
  
  GIVEN("An ACE Table for 1000.mp1"){
    
    const auto mp1 = interpretation::MP1( table );
    const auto txs = mp1.totalCrossSection( );

    
    auto package = ranges::view::zip( txs.values(1), txs.values(2), txs.values(8) );
    
    // for ( auto tupe : package ) {
    //   std::cout << std::get<0>(tupe) << " "
    // 		<< std::get<1>(tupe) << " "
    // 		<< std::get<2>(tupe) << std::endl;
    // }
  }
}




