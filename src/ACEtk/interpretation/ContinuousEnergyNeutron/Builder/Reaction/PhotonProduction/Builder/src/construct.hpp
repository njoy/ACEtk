PhotonProduction construct(){
  try{
    return PhotonProduction{
      MT,
      std::move( crossSection_.value() ),
      std::move( angularDistribution_.value() ),
      std::move( energyDistribution_ )
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating a PhotonProduction object" );
    Log::info( "Some component has not been defined" );
    throw;
  }
}
