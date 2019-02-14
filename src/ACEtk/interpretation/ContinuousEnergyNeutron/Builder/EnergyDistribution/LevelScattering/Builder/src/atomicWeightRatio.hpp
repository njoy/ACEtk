Builder& atomicWeightRatio( double awr ){
  if( awr < 0.0 ){
    Log::error( "Atomic weight ratio must be postive" );
    Log::info( "Received AWR: {}", awr );
    throw std::exception();
  }

  this->atomicWeightRatio_ = awr;
  return *this;
}
