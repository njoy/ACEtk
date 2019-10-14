Builder& numberDiscretePhotonLines( int N ){
  if( N <= 0 ){
    Log::error( "Number of discrete photon lines must be greater than 0." );
    Log::info( "Given value of {}", N );
    throw std::exception();
  }

  this->numberDiscretePhotonLines_ = N;
  return *this;
}
