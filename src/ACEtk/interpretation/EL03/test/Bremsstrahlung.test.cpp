#include "catch.hpp"
#include "ACEtk.hpp"
#include <map>

namespace interpretation = njoy::ACEtk::interpretation;

extern std::array< double, 57 > referenceElectronEnergy;
extern std::array< double, 57 > referenceValues;

SCENARIO( "test interperatation::EL03::Bremsstrahlung" ) {
  auto table = njoy::ACEtk::Table( njoy::utility::slurpFileToMemory( "1000.e03" ) );

  GIVEN( "An ACE Table for 1000.03e" ) {
    const auto el03_brems = interpretation::EL03( table ).bremsstrahlung();
    const auto production_xs = el03_brems.productionCrossSection();
    const auto outgoing_dist = el03_brems.outgoingDistributions();        

    WHEN( "Querying for the electron energy values" ) {
      for ( const auto pair : ranges::view::zip( referenceElectronEnergy,
						 production_xs.electron_energies() ) ) {
	  REQUIRE( pair.first == Approx( pair.second.value ) );
      }
    }

    WHEN( "Querying for the photon to electron energy ratio values" ) {
      const std::map< int, double > referenceRatio {
	{  0, 0.000000000000E+00 }, {  8, 4.000000000000E-01 },
	{ 16, 8.000000000000E-01 }, { 24, 9.990000000000E-01 },
	{ 29, 1.000000000000E+00 } };

      const auto photonRatio = production_xs.photonElectronEnergyRatio();

      for ( const auto& pair : referenceRatio ) {
	const auto index = pair.first;
	const auto value = pair.second;
	REQUIRE( photonRatio[index] == Approx( value ) );
      }
    }

    WHEN( "Querying for the values the cross section grid for Bremstrahlung"  ) {
      for ( const auto pair : ranges::view::zip( referenceValues,
						 production_xs.values().front()) ) {
	REQUIRE( pair.first == Approx( pair.second.value ) );
      }      
    }

    WHEN( "Querying for the ratio of photon energy over electron energy "
	  "values for bremsstrahlung spectrum calculation" ) {
      const std::map< int, double > spectrumReference{
	{  0, 1.000000000000E-06 }, { 24, 1.000000000000E-03 },
	{ 48, 4.000000000000E-02 }, { 72, 5.000000000000E-01 },
	{ 88, 1.000000000000E+00 } };
      
      const auto spectrum = outgoing_dist.photonElectronRatiosForEnergy();

      for ( const auto& pair : spectrumReference ) {
	const auto index = pair.first;
	const auto value = pair.second;
	REQUIRE( spectrum[index] == Approx( value ) );
      }
    }

    WHEN( "Querying for the ratio of photon energy over electron energy "
	  "ratio values for bremsstrahlung angular distribution" ) {
      const std::map< int, double > angularDistributionReference{
	{  0, 9.999000000000E-01 }, {  8, 1.000000000000E-01 },
	{ 16, 1.000000000000E-02 }, { 24, 1.000000000000E-03 },
	{ 33, 1.000000000000E-06 }    };

      const auto angularDistribution =
	outgoing_dist.photonElectronRatiosForAngle();

      for ( const auto& pair : angularDistributionReference ) {
	const auto index = pair.first;
	const auto value = pair.second;
	REQUIRE( angularDistribution[index] == Approx( value ) );
      }
    }	
  }	  
}

std::array< double, 57 >  referenceElectronEnergy = {{
      1.000000000000E-03, 1.500000000000E-03, 2.000000000000E-03,
      3.000000000000E-03, 4.000000000000E-03, 5.000000000000E-03,
      6.000000000000E-03, 8.000000000000E-03, 1.000000000000E-02,
      1.500000000000E-02, 2.000000000000E-02, 3.000000000000E-02,
      4.000000000000E-02, 5.000000000000E-02, 6.000000000000E-02,
      8.000000000000E-02, 1.000000000000E-01, 1.500000000000E-01,
      2.000000000000E-01, 3.000000000000E-01, 4.000000000000E-01,
      5.000000000000E-01, 6.000000000000E-01, 8.000000000000E-01,
      1.000000000000E+00, 1.500000000000E+00, 2.000000000000E+00,
      3.000000000000E+00, 4.000000000000E+00, 5.000000000000E+00,
      6.000000000000E+00, 8.000000000000E+00, 1.000000000000E+01,
      1.500000000000E+01, 2.000000000000E+01, 3.000000000000E+01,
      4.000000000000E+01, 5.000000000000E+01, 6.000000000000E+01,
      8.000000000000E+01, 1.000000000000E+02, 1.500000000000E+02,
      2.000000000000E+02, 3.000000000000E+02, 4.000000000000E+02,
      5.000000000000E+02, 6.000000000000E+02, 8.000000000000E+02,
      1.000000000000E+03, 1.500000000000E+03, 2.000000000000E+03,
      3.000000000000E+03, 4.000000000000E+03, 5.000000000000E+03,
      6.000000000000E+03, 8.000000000000E+03, 1.000000000000E+04 }};

std::array< double, 57 >  referenceValues = {{
      7.853270000000E-03, 8.385290000000E-03, 8.805280000000E-03,
      9.446420000000E-03, 9.929790000000E-03, 1.031651000000E-02,
      1.063768000000E-02, 1.114991000000E-02, 1.155073000000E-02,
      1.229079000000E-02, 1.306510000000E-02, 1.383092000000E-02,
      1.440859000000E-02, 1.490026000000E-02, 1.535082000000E-02,
      1.619688000000E-02, 1.693994000000E-02, 1.873528000000E-02,
      2.030812000000E-02, 2.325490000000E-02, 2.573999000000E-02,
      2.789619000000E-02, 2.980029000000E-02, 3.299527000000E-02,
      3.556744000000E-02, 4.025667000000E-02, 4.342175000000E-02,
      4.738277000000E-02, 4.985606000000E-02, 5.130644000000E-02,
      5.254506000000E-02, 5.420055000000E-02, 5.523288000000E-02,
      5.659717000000E-02, 5.728667000000E-02, 5.804907000000E-02,
      5.833458000000E-02, 5.835318000000E-02, 5.816777000000E-02,
      5.772517000000E-02, 5.729999000000E-02, 5.636497000000E-02,
      5.500314000000E-02, 5.163249000000E-02, 4.877057000000E-02,
      4.669637000000E-02, 4.526547000000E-02, 4.344806000000E-02,
      4.229637000000E-02, 4.054385000000E-02, 3.954947000000E-02,
      3.848796000000E-02, 3.792909000000E-02, 3.757637000000E-02,
      3.732846000000E-02, 3.700685000000E-02, 3.681818000000E-02 }};
