EvaporationSpectrum construct(){

  try{
    return EvaporationSpectrum{ 
      TabBuilder::construct(), 
      std::move( restrictionEnergy_.value() ) };
  } catch( std::bad_optional_access& b ){
    Log::error( "Some Evaporation Spectrum compontent not built." );
    throw;
  }
}
