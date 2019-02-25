GeneralEvaporationSpectrum construct(){

  try{
    return GeneralEvaporationSpectrum{ 
      TabBuilder::construct(), 
      std::move( spectrum_.value() ) };
  } catch( std::bad_optional_access& b ){
    Log::error( "Some General Evaporation Spectrum compontent not built." );
    throw;
  }
}
