Equiprobable construct() {
  try{
    return Equiprobable{
      std::move( this->cosineBins_.value() )
    };
  } catch( std::bad_optional_access& b ){
    Log::error( "Trouble when creating a "
                "Reaction::AngularDistribution::Equiprobable object" );
    Log::info( "Some component has not been defined" );
    throw;
  }
}
