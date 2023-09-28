#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

extern std::array< double, 22 > bindingEnergiesGold;
extern std::array< double, 22 > occupationNumbersGold;
extern std::array< bool, 22 > isConductiveGold;

SCENARIO("test AtomicLevels"){


  GIVEN("An ACE Table for 1000.e03"){
    auto table = Table( njoy::utility::slurpFileToMemory("1000.el03") );
    auto atomicLevel =
      interpretation::EL03::AtomicLevels( table ).values();

    REQUIRE( std::get<0>(atomicLevel[0]) == 1 );
    REQUIRE( std::get<1>(atomicLevel[0]) == false );
    REQUIRE( std::get<2>(atomicLevel[0]) == 13.6 * electronVolt );

  }


  GIVEN("An ACE Table for 79000.e03"){
    auto table = Table( njoy::utility::slurpFileToMemory("79000.el03") );
    const auto atomicLevels = interpretation::EL03::AtomicLevels( table );
    const auto compareThese = ranges::views::zip( occupationNumbersGold,
						 isConductiveGold,
						 bindingEnergiesGold );
    for ( const auto pair : ranges::views::zip( atomicLevels.values(), compareThese ) ) {

      auto occNumRef = std::get<0>(pair.second);
      REQUIRE( std::get<0>(pair.first) == Approx( occNumRef ).epsilon(1e-15) );

      auto isCondRef = std::get<1>(pair.second);
      REQUIRE( std::get<1>(pair.first) == isCondRef );

      auto bindErgRef = std::get<2>(pair.second);
      REQUIRE( std::get<2>(pair.first).value == Approx( bindErgRef ).epsilon(1e-15) );

    }

  }
}

  std::array< double, 22 > bindingEnergiesGold = {{
      8.072900000000E+04,  1.435600000000E+04,  1.373800000000E+04,
      1.192300000000E+04,  3.430000000000E+03,  3.153000000000E+03,  2.748000000000E+03,
      2.295000000000E+03,  2.210000000000E+03,  7.640000000000E+02,  6.450000000000E+02,
      5.480000000000E+02,  3.570000000000E+02,  3.390000000000E+02,  9.100000000000E+01,
      8.700000000000E+01,  1.140000000000E+02,  7.600000000000E+01,  6.100000000000E+01,
      1.250000000000E+01,  1.110000000000E+01,  9.230000000000E+00
    }};

  std::array< double, 22 > occupationNumbersGold = {{
      2.000000000000E+00,
      2.000000000000E+00,  2.000000000000E+00,  4.000000000000E+00,  2.000000000000E+00,
      2.000000000000E+00,  4.000000000000E+00,  4.000000000000E+00,  6.000000000000E+00,
      2.000000000000E+00,  2.000000000000E+00,  4.000000000000E+00,  4.000000000000E+00,
      6.000000000000E+00,  6.000000000000E+00,  8.000000000000E+00,  2.000000000000E+00,
      2.000000000000E+00,  4.000000000000E+00,  4.000000000000E+00,  6.000000000000E+00,
      1.000000000000E+00
    }};

  std::array< bool, 22 > isConductiveGold = {{
      false, false, false, false, false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, false, false, false, true
    }};
