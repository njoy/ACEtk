PhotonProductionReaction construct(){
  if( yields_ and crossSection_ ){
    Log::error( 
      "Either photon production yields or cross sections can be given; "
      "not both." );
    throw std::exception();
  }
  try{
    return PhotonProductionReaction{
      MT,
      yields_,
      crossSection_,
      angularDistribution_.value(),
      energyDistribution_.value()
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating a PhotonProductionReaction object" );
    Log::info( "Some component has not been defined" );
    throw;
  }
}