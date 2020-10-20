Builder& atomicWeightRatio( double awr ){
  if( awr < 0.0 ){
    Log::error( "atomic weight ratio must be positive" );
    throw std::exception();
  }

  this->atomicWeightRatio_ = awr;
  return *this;
}
