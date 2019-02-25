EnergyDependentWattSpectrum construct(){
  if( not aTabulated_ ){
    Log::info( "aTabulated not built" );
  }
  if( not bTabulated_ ){
    Log::info( "bTabulated not built" );
  }
  try{
    return EnergyDependentWattSpectrum{ 
      std::move( aTabulated_.value() ),
      std::move( bTabulated_.value() ),
      restrictionEnergy_.value()

    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Part of Energy Dependent Watt Spectrum not yet built." );
    throw;
  }
}
