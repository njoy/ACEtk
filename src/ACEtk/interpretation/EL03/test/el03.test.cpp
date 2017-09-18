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

    WHEN("Querying for the energy grid in MeV,"
	 "on which the radiative stopping interpolation are evaluated") {
      const auto trial = el03.radiativeStoppingPower().energyGrid(); 
      const auto reference = referenceEnergyGrid | ranges::view::reverse;
      for( const auto pair : ranges::view::zip( reference, trial ) ) {
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





/*

  std::array< double, 57 > refBremssCorrection = {{
      1.149660000000E+00, 1.148810000000E+00, 1.147510000000E+00,
      1.146550000000E+00, 1.145260000000E+00, 1.143380000000E+00,
      1.140440000000E+00, 1.137900000000E+00, 1.133630000000E+00,
      1.130970000000E+00, 1.127410000000E+00, 1.125180000000E+00,
      1.122570000000E+00, 1.118770000000E+00, 1.111000000000E+00,
      1.102700000000E+00, 1.087820000000E+00, 1.078640000000E+00,
      1.065830000000E+00, 1.056910000000E+00, 1.045100000000E+00,
      1.028610000000E+00, 1.003120000000E+00, 9.833800000000E-01,
      9.528600000000E-01, 9.345200000000E-01, 9.081500000000E-01,
      8.893600000000E-01, 8.648800000000E-01, 8.273500000000E-01,
      7.633800000000E-01, 7.091500000000E-01, 6.215400000000E-01,
      5.689600000000E-01, 4.977000000000E-01, 4.514900000000E-01,
      3.950600000000E-01, 3.250800000000E-01, 2.375100000000E-01,
      1.859000000000E-01, 1.285200000000E-01, 1.041300000000E-01,
      7.893000000000E-02, 6.607000000000E-02, 5.308000000000E-02,
      3.998000000000E-02, 2.673000000000E-02, 2.002000000000E-02,
      1.330000000000E-02, 1.059000000000E-02, 7.880000000000E-03,
      6.520000000000E-03, 5.160000000000E-03, 3.800000000000E-03,
      2.460000000000E-03, 1.770000000000E-03, 1.140000000000E-03 }};

    WHEN("Querying for the electron-electron bremmstrahlung correction evaluation points"){
      
      const auto bremsstrahlungCorrections = interpretation.bremsstrahlungCorrection();      

      auto compareThese = ranges::view::zip( std::reverse( refBremssCorrection.begin( ),
							   refBremssCorrection.end( ) ),
					     bremsstrahlungCorrections );
      
      for( const auto pair : compareThese ) {
	REQUIRE( pair.first == Approx( pair.second ).epsilon( 1e-15 ) );
      }
    }     
    */
