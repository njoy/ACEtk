LevelScattering construct(){
  try {
    return { QValue_.value(), atomicWeightRatio_.value() };
  } catch( std::bad_optional_access& ){
    Log::info( "Some component of LevelScattering not built." );
    throw;
  }
}
