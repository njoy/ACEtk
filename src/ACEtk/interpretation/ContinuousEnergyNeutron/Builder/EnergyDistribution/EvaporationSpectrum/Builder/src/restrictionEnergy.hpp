Builder& restrictionEnergy( double energy ){
  if( energy < 0.0 ){
    Log::error( "restriction energy must be >= 0.0" );
    Log::info( "received restriction energy = {}", energy );
    throw std::exception();
  }

  this->restrictionEnergy_ = energy;
  return *this;
}
