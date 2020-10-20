Builder& totalMassRatio( double A ){
  if( A < 0.0 ){
    Log::error( "Total mass ratio must be >= 0.0." );
    Log::info( "Given A={}", A );
    throw std::exception();
  }
  totalMassRatio_ = A;
  return *this;
}

