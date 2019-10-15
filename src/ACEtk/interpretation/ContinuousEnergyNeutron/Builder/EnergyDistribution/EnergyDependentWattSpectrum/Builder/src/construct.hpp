EnergyDependentWattSpectrum construct(){
  try{
    return EnergyDependentWattSpectrum{ 
      std::move( aTabulated_.value() ),
      std::move( bTabulated_.value() ),
      restrictionEnergy_.value()
    };
  } catch( std::bad_optional_access& b ){
    Log::error( 
      "Some component of Energy Dependent Watt Spectrum not yet built." );
    throw;
  }
}
