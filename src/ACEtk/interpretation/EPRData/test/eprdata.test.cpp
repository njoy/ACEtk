#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"
#include <map>

using namespace njoy::ACEtk;

SCENARIO( "Test interpretation::EPRdata::ESZG" ){
  auto table = Table{ njoy::utility::slurpFileToMemory( "1000.14p" ) };

  GIVEN( "An ACE table for 1000.14p" ){
    const auto eprdata = interpretation::EPRData{ std::move(table) };
    
    WHEN( "Querying for the energy grid" ) {
      const std::map< int, double > referencePhotonEnergies{
    	{   0, 1.000000000000E-06 },
    	{  64, 8.013002999974E-06 },
    	{ 129, 1.017127000001E-05 },
    	{ 194, 1.167710000005E-05 },
    	{ 259, 1.249504000002E-05 },
    	{ 324, 2.788451999999E-05 },
    	{ 389, 3.101247999991E-03 },
    	{ 454, 7.413102000002E-01 },
        { 519, 2.745299999992E+00 },
    	{ 584, 7.943300000026E+01 },
    	{ 646, 1.000000000000E+05 } };

      const auto photonEnergies = eprdata.eszg().energies();

      for ( const auto& pair : referencePhotonEnergies ){
      	const auto index = pair.first;
      	const auto reference = pair.second;
      	REQUIRE( photonEnergies[ index ].value == Approx( reference ).epsilon( 1e-8 ) );
      }
      }
    
    WHEN( "Querying for the incoherent scattering cross sections" ){
      const std::map< int, double > referenceIncoherentXS{
  	{   0, 9.562300000011E-08 },
  	{  65, 6.233095862891E-06 },
  	{ 130, 9.913960683988E-06 },
  	{ 195, 1.305571253645E-05 },
  	{ 260, 1.494693970558E-05 },
  	{ 325, 7.594369400331E-05 },
  	{ 390, 3.997974532085E-01 },
  	{ 455, 2.356200069564E-01 },
  	{ 520, 1.196748005439E-01 },
  	{ 585, 9.876644877527E-03 },
  	{ 646, 1.704199999997E-05 } };
      
      const auto incoherentScatteringXS = eprdata.eszg().incoherentScatteringXS();
      
      for ( const auto& pair : referenceIncoherentXS ){
  	const auto index = pair.first;
  	const auto reference = pair.second;
  	REQUIRE( incoherentScatteringXS[ index ].value == Approx( reference ) );
      }
    }

    WHEN( "Querying for the coherent scattering cross sections" ){
      const std::map< int, double > referenceCoherentXS{
  	{   0, 9.887553000014E-06 },
  	{  65, 3.361804999998E-01 },
  	{ 130, 4.768264000007E+02 },
  	{ 195, 1.769341000000E-01 },
  	{ 260, 1.616027000000E+00 },
  	{ 325, 1.036825798528E+00 },
  	{ 390, 2.587707888495E-01 },
  	{ 455, 7.331701968226E-06 },
  	{ 520, 5.862947790958E-07 },
  	{ 585, 7.228371741121E-10 },
  	{ 646, 4.626159999988E-16 } };
      
      const auto coherentScatteringXS = eprdata.eszg().coherentScatteringXS();
      
      for ( const auto& pair : referenceCoherentXS ){
  	const auto index = pair.first;
  	const auto reference = pair.second;
  	REQUIRE( coherentScatteringXS[ index ].value == Approx( reference ) );
      }
    }

    WHEN( "Querying for the total photoelectric cross sections" ){
      const std::map< int, double > referencePhotoelectricXS{
  	{   0, 0.000000000000E+00 },
  	{ 260, 0.000000000000E+00 },
  	{ 325, 8.425752000037E+05 },
  	{ 390, 2.345066984180E-01 },
  	{ 455, 3.161881017536E-09 },
  	{ 520, 3.844938856038E-10 },
  	{ 585, 9.793289828319E-12 },
  	{ 646, 7.735999999998E-15 } };

      const auto photoelectricXS = eprdata.eszg().photoelectricXS();

      for ( const auto& pair : referencePhotoelectricXS ){
  	const auto index = pair.first;
  	const auto reference = pair.second;
  	REQUIRE( photoelectricXS[ index ].value == Approx( reference ) );
      }
    }

    WHEN( "Querying for the pair-production cross sections" ){
      const std::map< int, double > referencePairProductionXS{
  	{   0, 0.000000000000E+00 },
  	{ 455, 0.000000000000E+00 },
  	{ 520, 4.644311999999E-04 },
  	{ 585, 1.086700000001E-02 },
  	{ 646, 2.070099999999E-02 } };

      const auto pairProductionXS = eprdata.eszg().pairProductionXS();

      for ( const auto& pair : referencePairProductionXS ){
  	const auto index = pair.first;
  	const auto reference = pair.second;
  	REQUIRE( pairProductionXS[ index ].value == Approx( reference ) );
      }
    }
  }
}
