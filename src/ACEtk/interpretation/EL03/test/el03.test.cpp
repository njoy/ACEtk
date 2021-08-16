#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

namespace{

  std::array< double, 57 > referenceEnergyGrid = {{
      1.000000000000E+04, 8.000000000000E+03, 6.000000000000E+03,
      5.000000000000E+03, 4.000000000000E+03, 3.000000000000E+03,
      2.000000000000E+03, 1.500000000000E+03, 1.000000000000E+03,
      8.000000000000E+02, 6.000000000000E+02, 5.000000000000E+02,
      4.000000000000E+02, 3.000000000000E+02, 2.000000000000E+02,
      1.500000000000E+02, 1.000000000000E+02, 8.000000000000E+01,
      6.000000000000E+01, 5.000000000000E+01, 4.000000000000E+01,
      3.000000000000E+01, 2.000000000000E+01, 1.500000000000E+01,
      1.000000000000E+01, 8.000000000000E+00, 6.000000000000E+00,
      5.000000000000E+00, 4.000000000000E+00, 3.000000000000E+00,
      2.000000000000E+00, 1.500000000000E+00, 1.000000000000E+00,
      8.000000000000E-01, 6.000000000000E-01, 5.000000000000E-01,
      4.000000000000E-01, 3.000000000000E-01, 2.000000000000E-01,
      1.500000000000E-01, 1.000000000000E-01, 8.000000000000E-02,
      6.000000000000E-02, 5.000000000000E-02, 4.000000000000E-02,
      3.000000000000E-02, 2.000000000000E-02, 1.500000000000E-02,
      1.000000000000E-02, 8.000000000000E-03, 6.000000000000E-03,
      5.000000000000E-03, 4.000000000000E-03, 3.000000000000E-03,
      2.000000000000E-03, 1.500000000000E-03, 1.000000000000E-03 }};
}

SCENARIO("test interpretation::EL03"){
  auto table = Table( njoy::utility::slurpFileToMemory("1000.e03") );

  GIVEN("An ACE Table for 1000.e03"){
    const auto el03 = interpretation::EL03( table );

    WHEN("querying for the target atomic number"){
      REQUIRE( el03.atomicNumber() == 1 );
    }

    WHEN("Querying for the energy grid in MeV,"
	 "on which the radiative stopping interpolation are evaluated") {
      const auto trial = el03.radiativeStoppingPower().energyGrid();
      const auto reference = referenceEnergyGrid | ranges::cpp20::views::reverse;
      for( const auto pair : ranges::views::zip( reference, trial ) ) {
	REQUIRE( pair.first == Approx( pair.second.value ) );
      }
    }

    WHEN("Querying for the radiative stopping power evaluation points"){
      const std::map< int, double > mcnpReference{
        { 0, 1.5709714430603072E-003 },
        { 24, 8.5914575611197690E-003 },
        { 56, 266.13402564187817 } };

      const auto stoppingPowers = el03.radiativeStoppingPower().values();

      for ( const auto& pair : mcnpReference ){
        const auto index = pair.first;
        const auto reference = pair.second;
        REQUIRE( stoppingPowers[index].value * 1e28
                 ==  Approx( reference ).epsilon( 1e-4 ) );
      }
    }
  }
}
