#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

namespace{

  std::array< double, 9 > referenceEnergyGrid = {{
      2.560000000000E+02, 1.280000000000E+02, 6.400000000000E+01,
      3.200000000000E+01, 1.600000000000E+01, 8.000000000000E+00,
      4.000000000000E+00, 2.000000000000E+00, 1.000000000000E+00 }};      
}

SCENARIO( "test interpretation::EL03::MottScatteringCorrection" ){  
  auto table = Table( njoy::utility::slurpFileToMemory("1000.e03") );

  GIVEN( "An ACE Table for 1000.03e" ) {
    const auto el03 = interpretation::EL03( table );

    WHEN( "Queing for the energy grid in MeV, "
	  "on which the Mott Scattering Corrections are evaluated" ) {
      const auto trial = el03.mottScatteringCorrection().energyGrid();
      const auto reference = referenceEnergyGrid | ranges::view::reverse;
      for ( const auto pair : ranges::view::zip( reference, trial ) ) {
	REQUIRE( pair.first == Approx( pair.second.value ) );
      }
    }

    WHEN( "Queing for the Motts scattering correction points" ) {
      //const auto mcorrection = el03.mottScatteringCorrection().values();
    }

  }
}
