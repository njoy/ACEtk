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

  std::array< double, 57 > refEvaluations= {{  
      2.136440000000E+01,
      2.134340000000E+01,  2.130791000000E+01,  2.128101000000E+01,  2.124249000000E+01,
      2.118210000000E+01,  2.106950000000E+01,  2.097020000000E+01,  2.079390000000E+01,
      2.067419000000E+01,  2.049170000000E+01,  2.035789000000E+01,  2.017230000000E+01,
      1.989639000000E+01,  1.942900000000E+01,  1.903630000000E+01,  1.839030000000E+01,
      1.798621000000E+01,  1.741209000000E+01,  1.701830000000E+01,  1.650320000000E+01,
      1.578480000000E+01,  1.467370000000E+01,  1.382350000000E+01,  1.255910000000E+01,
      1.184060000000E+01,  1.090830000000E+01,  1.032100000000E+01,  9.599990000000E+00,
      8.714690000000E+00,  7.571310000000E+00,  6.867790000000E+00,  6.051420000000E+00,
      5.696110000000E+00,  5.341790000000E+00,  5.175060000000E+00,  5.028350000000E+00,
      4.924720000000E+00,  4.907630000000E+00,  4.949440000000E+00,  5.045750000000E+00,
      5.101910000000E+00,  5.170810000000E+00,  5.207790000000E+00,  5.244590000000E+00,
      5.273570000000E+00,  5.289890000000E+00,  5.296510000000E+00,  5.287470000000E+00,
      5.280360000000E+00,  5.272320000000E+00,  5.268760000000E+00,  5.266160000000E+00,
      5.265870000000E+00,  5.271560000000E+00,  5.278690000000E+00,  5.289160000000E+00 }};

  std::array< double, 57 > refCorrectionEvaluations= {{
      1.149660000000E+00,  1.148810000000E+00,  1.147510000000E+00,  1.146550000000E+00,
      1.145260000000E+00,  1.143380000000E+00,  1.140440000000E+00,  1.137900000000E+00,
      1.133630000000E+00,  1.130970000000E+00,  1.127410000000E+00,  1.125180000000E+00,
      1.122570000000E+00,  1.118770000000E+00,  1.111000000000E+00,  1.102700000000E+00,
      1.087820000000E+00,  1.078640000000E+00,  1.065830000000E+00,  1.056910000000E+00,
      1.045100000000E+00,  1.028610000000E+00,  1.003120000000E+00,  9.833800000000E-01,
      9.528600000000E-01,  9.345200000000E-01,  9.081500000000E-01,  8.893600000000E-01,
      8.648800000000E-01,  8.273500000000E-01,  7.633800000000E-01,  7.091500000000E-01,
      6.215400000000E-01,  5.689600000000E-01,  4.977000000000E-01,  4.514900000000E-01,
      3.950600000000E-01,  3.250800000000E-01,  2.375100000000E-01,  1.859000000000E-01,
      1.285200000000E-01,  1.041300000000E-01,  7.893000000000E-02,  6.607000000000E-02,
      5.308000000000E-02,  3.998000000000E-02,  2.673000000000E-02,  2.002000000000E-02,
      1.330000000000E-02,  1.059000000000E-02,  7.880000000000E-03,  6.520000000000E-03,
      5.160000000000E-03,  3.800000000000E-03,  2.460000000000E-03,  1.770000000000E-03,
      1.140000000000E-03 }};
      
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
  }

  GIVEN("An interpretation for 1000.e03"){
    
    Interpretation< El03 > interpretation( table );          

    WHEN("Querying for the energy grid in MeV,"
	 "on which the radiative stopping interpolation are evaluated") {
      const auto energyGrid = interpretation.energyGrid( El03::RadiativeStopping{} );      
      auto compareThese = ranges::view::zip( refEnergyGrid, energyGrid );
      for( const auto pair : compareThese ) {
	REQUIRE( pair.first == Approx( pair.second ).epsilon( 1e-15 ) );
      }
    }

    WHEN("Querying for the radiative stopping power evaluation points"){
      const auto evaluations = interpretation.evaluations( El03::RadiativeStopping{} );      
      auto compareThese = ranges::view::zip( refEvaluations, evaluations );
      for( const auto pair : compareThese ) {
	REQUIRE( pair.first == Approx( pair.second ).epsilon( 1e-15 ) );
      }
    }
    
    WHEN("Querying for the electron-electron bremmstrahlung correction evaluation points"){
      const auto evaluations = interpretation.evaluations( El03::BremsstrahlungCorrection{} );      
      auto compareThese = ranges::view::zip( refCorrectionEvaluations, evaluations );
      for( const auto pair : compareThese ) {
	REQUIRE( pair.first == Approx( pair.second ).epsilon( 1e-15 ) );
      }
    }        
    
    
  }
}
