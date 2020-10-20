Builder& energy( double energy ){
  if( energy < 0.0 ){
    Log::error( "Discrete photon energy must be >= 0.0" );
    Log::info( "Given energy value: {}", energy );
    throw std::exception();
  }
  energy_ = energy;
  return *this;
}
