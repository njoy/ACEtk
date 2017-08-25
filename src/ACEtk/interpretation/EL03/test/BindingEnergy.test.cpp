#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

namespace{

  std::array< double, 22 > bindingEnergiesGold = {{
      8.072900000000E+04,  1.435600000000E+04,  1.373800000000E+04,
      1.192300000000E+04,  3.430000000000E+03,  3.153000000000E+03,  2.748000000000E+03,
      2.295000000000E+03,  2.210000000000E+03,  7.640000000000E+02,  6.450000000000E+02,
      5.480000000000E+02,  3.570000000000E+02,  3.390000000000E+02,  9.100000000000E+01,
      8.700000000000E+01,  1.140000000000E+02,  7.600000000000E+01,  6.100000000000E+01,
      1.250000000000E+01,  1.110000000000E+01,  9.230000000000E+00}};

}

SCENARIO("test BindingEnergy"){  

  GIVEN("An ACE Table for 1000.e03"){
    auto table = Table( njoy::utility::slurpFileToMemory("1000.el03") );
    const auto bindingEnergy = interpretation::EL03::BindingEnergy( table );
    auto singleEntryForH1 = bindingEnergy.values()[0]; 
    REQUIRE( singleEntryForH1 == 13.6 * electronVolt );
  }

  GIVEN("An ACE Table for 79000.e03"){
    auto table = Table( njoy::utility::slurpFileToMemory("79000.el03") );
    const auto bindingEnergies = interpretation::EL03::BindingEnergy( table );
    for ( const auto pair : ranges::view::zip( bindingEnergies.values(),
					       bindingEnergiesGold) ){
      REQUIRE( pair.first.value == Approx( pair.second ).epsilon( 1e-15 ) );
    }
  }  
}

