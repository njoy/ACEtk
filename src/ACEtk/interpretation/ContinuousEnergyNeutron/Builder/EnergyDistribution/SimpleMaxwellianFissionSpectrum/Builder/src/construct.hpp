SimpleMaxwellianFissionSpectrum construct(){

  try{
    return SimpleMaxwellianFissionSpectrum{ 
      TabBuilder::construct(), 
      std::move( restrictionEnergy_.value() ) };
  } catch( std::bad_optional_access& b ){
    Log::error( 
      "Some Simple Maxwellian Fission Spectrum compontent not built." );
    throw;
  }
}
