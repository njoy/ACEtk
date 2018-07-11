#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

namespace{

  std::array< double, 18 > referenceEnergyGrid = {{
      1.000000000000E+03, 1.000000000000E+02, 1.000000000000E+01,
      7.000000000000E+00, 4.000000000000E+00, 2.000000000000E+00,
      1.000000000000E+00, 7.000000000000E-01, 4.000000000000E-01,
      2.000000000000E-01, 1.000000000000E-01, 7.000000000000E-02,
      4.000000000000E-02, 2.000000000000E-02, 1.000000000000E-02,
      5.000000000000E-03, 1.000000000000E-03, 1.000000000000E-04 }};

  std::array< double, 5 > referenceMottCorrections1 = {{
	1.000000000000E+00, 8.589500000000E-01, 5.057200000000E-01,
	1.472600000000E-01, 0.000000000000E+00 }};

    std::array< double, 5 > referenceMottCorrections2 = {{
	1.000000000000E+00, 1.000080000000E+00, 9.999400000000E-01,
	9.998300000000E-01, 9.997200000000E-01 }};

}

SCENARIO("test interpretation::EL03::MottScatteringCorrection.hpp"){  
  auto table = Table( njoy::utility::slurpFileToMemory("1000.e03") );
  
  GIVEN("An ACE Table for 1000.e03"){
    const auto el03 = interpretation::EL03( table );

    WHEN("Querying for the energy grid in MeV,"
	 "on which the mott scattering correction data are evaluated") {
      const auto trial = el03.mottScatteringCorrection().energyGrid();
      const auto reference = referenceEnergyGrid | ranges::view::reverse;
      for ( const auto pair : ranges::view::zip( reference, trial ) ) {
	REQUIRE( pair.first == Approx( pair.second.value ) );
      }
    }
    
    WHEN("Querying for the Mott scattering correction data"){
      const auto mottCorrectionValues = el03.mottScatteringCorrection().values();
      for ( const auto pair
	      : ranges::view::zip( referenceMottCorrections1, mottCorrectionValues[17] ) ) {
	REQUIRE( pair.first == Approx( pair.second ) );
      }
      
      for ( const auto pair
	      : ranges::view::zip( referenceMottCorrections2, mottCorrectionValues[0] ) ) {
	REQUIRE( pair.first == Approx( pair.second ) );
      }      
    }
  }
}

