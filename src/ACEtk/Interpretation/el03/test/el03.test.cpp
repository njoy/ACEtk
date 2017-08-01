#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;


namespace{
  std::array< double, 57 > refEnergyGrid= {{
      1.000000000000E+04,  8.000000000000E+03,
      6.000000000000E+03,  5.000000000000E+03,  4.000000000000E+03,  3.000000000000E+03,
      2.000000000000E+03,  1.500000000000E+03,  1.000000000000E+03,  8.000000000000E+02,
      6.000000000000E+02,  5.000000000000E+02,  4.000000000000E+02,  3.000000000000E+02,
      2.000000000000E+02,  1.500000000000E+02,  1.000000000000E+02,  8.000000000000E+01,
      6.000000000000E+01,  5.000000000000E+01,  4.000000000000E+01,  3.000000000000E+01,
      2.000000000000E+01,  1.500000000000E+01,  1.000000000000E+01,  8.000000000000E+00,
      6.000000000000E+00,  5.000000000000E+00,  4.000000000000E+00,  3.000000000000E+00,
      2.000000000000E+00,  1.500000000000E+00,  1.000000000000E+00,  8.000000000000E-01, 
      6.000000000000E-01,  5.000000000000E-01,  4.000000000000E-01,  3.000000000000E-01,
      2.000000000000E-01,  1.500000000000E-01,  1.000000000000E-01,  8.000000000000E-02,
      6.000000000000E-02,  5.000000000000E-02,  4.000000000000E-02,  3.000000000000E-02,
      2.000000000000E-02,  1.500000000000E-02,  1.000000000000E-02,  8.000000000000E-03,
      6.000000000000E-03,  5.000000000000E-03,  4.000000000000E-03,  3.000000000000E-03,
      2.000000000000E-03,  1.500000000000E-03,  1.000000000000E-03, }};
}

SCENARIO("Testing XSS from el03"){  
  auto contents = njoy::utility::slurpFileToMemory("1000.e03");
  State< std::string::iterator > s{ 1, contents.begin(), contents.end() };  
  auto table = Table(s);

  
  GIVEN("The XSS array for 1000.e03"){
    
    WHEN("XSS( JXS(1) ) = XSS( 1 ),"
	 "K edge below which no electron induced relaxation will occur - keV...") {
      const auto index = table.data.JXS(1);
      REQUIRE( table.data.XSS( index ) == 1.4E-2 );
    }

    WHEN("XSS( JXS(1) + 1 ) = XSS( 1 + 1 ),"
	 "Auger electron emission energy") {
      const auto index = table.data.JXS(1) + 1;
      REQUIRE( table.data.XSS( index ) == 1.4E-2 );
    }

    WHEN("Querying XSS for the energies in MeV,"
	 "on which the radiative stopping interpolation are evaluated") {
      Interpretation< El03 > el03( table );          
      const auto energyGrid = el03.dependentVariable( El03::RadiativeStopping{} ); 
      auto compareThese = ranges::view::zip( refEnergyGrid, energyGrid );

      for( const auto pair : compareThese ) {
	REQUIRE( pair.first == Approx( pair.second ).epsilon( 1e-12 ) );
      }
      
    }

    
  }
}
