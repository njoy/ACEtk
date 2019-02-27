Builder& numberBodies( int N ){
  if( N < 0 ){
    Log::error( "Number of bodies in phase space must be >= 0" );
    Log::info( "Given N={}", N );
    throw std::exception();
  }
  numberBodies_ = N;
  return *this;
}
