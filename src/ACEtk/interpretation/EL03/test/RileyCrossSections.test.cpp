#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;

namespace{

  std::array< double, 9 > referenceEnergyGrid = {{
      2.560000000000E+02, 1.280000000000E+02, 6.400000000000E+01,
      3.200000000000E+01, 1.600000000000E+01, 8.000000000000E+00,
      4.000000000000E+00, 2.000000000000E+00, 1.000000000000E+00 }};      

  std::array< double, 13 > referenceRileyScatteringParameters1 = {{
      4.073883650000E-09, -1.335501900000E+00, 1.045778020000E+00,
      6.275424040000E-05,  1.268122540000E-07, 1.703313040000E+00,
      2.245204930000E+00,  1.800714760000E+00, 1.172297400000E+00,
      6.286648840000E-01,  2.593153900000E-01, 6.499743790000E-02,
      6.647650380000E-05 }};

    std::array< double, 13 > referenceRileyScatteringParameters2 = {{
	1.856727570000E-04, -3.216742330000E+00, 1.419727090000E+00,
	8.371867790000E-03, -1.262181140000E-04, 3.947374650000E+00,
	4.187353800000E+00,  2.718237740000E+00, 1.428939370000E+00,
	6.135402150000E-01,  1.985008800000E-01, 3.683759390000E-02,
	8.057218860000E-03 }};
}

SCENARIO( "test interpretation::EL03::RileyCrossSections.hpp" ){  
  auto table = Table( njoy::utility::slurpFileToMemory("1000.e03") );

  GIVEN( "An ACE Table for 1000.03e" ) {
    const auto el03 = interpretation::EL03( table );

    WHEN( "Quering for the energy points in MeV, "
	  "on which the Riley Scattering cross section are evaluated" ) {
      const auto rileyEnergy = el03.rileyCrossSections().energyGrid();
      const auto reference = referenceEnergyGrid | ranges::view::reverse;
      for ( const auto pair : ranges::view::zip( reference, rileyEnergy ) ) {
	REQUIRE( pair.first == Approx( pair.second.value ) );
      }
    }
    
    WHEN( "Quering for the Riley scattering correction parameters" ) {
      const auto riley_xs = el03.rileyCrossSections().values();
      const auto reference1 = referenceRileyScatteringParameters2;
      const auto reference2 = referenceRileyScatteringParameters1;

      for ( const auto pair : ranges::view::zip ( reference1, riley_xs[0] ) ) {
	REQUIRE( pair.first == Approx( pair.second ) );
      }
      
      for ( const auto pair : ranges::view::zip ( reference2, riley_xs[8] ) ) {
	REQUIRE( pair.first == Approx( pair.second ) );
      }
    }
  }
}
