Reaction::NonNeutronProducing constructNonNeutronProducing(){
  try{ 
    return Reaction::NonNeutronProducing{ 
      MT_, 
      Q_.value(),
      0,
      std::move( this->crossSection_.value() ),
      std::move( this->photonProduction_ )
    };
  } catch( std::bad_optional_access& ){
    Log::error( 
      "Trouble when creating a Reaction::NonNeutronProducing object." );
    Log::info( "Some component has not been defined." );
    throw;
  }
}
