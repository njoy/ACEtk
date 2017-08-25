#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

namespace{

  std::array< double, 22 > occupationNumbersGold = {{
      2.000000000000E+00,
      2.000000000000E+00,  2.000000000000E+00,  4.000000000000E+00,  2.000000000000E+00,
      2.000000000000E+00,  4.000000000000E+00,  4.000000000000E+00,  6.000000000000E+00,
      2.000000000000E+00,  2.000000000000E+00,  4.000000000000E+00,  4.000000000000E+00,
      6.000000000000E+00,  6.000000000000E+00,  8.000000000000E+00,  2.000000000000E+00,
      2.000000000000E+00,  4.000000000000E+00,  4.000000000000E+00,  6.000000000000E+00,
     -1.000000000000E+00 }};
}

SCENARIO("test OccupationNumber"){  

  GIVEN("An ACE Table for 1000.e03"){
    auto table = Table( njoy::utility::slurpFileToMemory("1000.el03") );
    const auto occNum = interpretation::EL03::OccupationNumber( table );
    auto singleEntryForH1 = occNum.values()[0]; 
    REQUIRE( singleEntryForH1 == 1 );
  }

  GIVEN("An ACE Table for 79000.e03"){
    auto table = Table( njoy::utility::slurpFileToMemory("79000.el03") );
    const auto occNum = interpretation::EL03::OccupationNumber( table );
    for ( const auto pair : ranges::view::zip( occNum.values(),
						occupationNumbersGold) ){
      REQUIRE( pair.first == pair.second );
    }
  }  
}

