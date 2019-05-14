PhotonProduction construct(){
  try{
    return PhotonProduction{
      MT,
      crossSection_.value(),
      angularDistribution_.value(),
      energyDistribution_.value()
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating a PhotonProduction object" );
    Log::info( "Some component has not been defined" );
    throw;
  }
}
