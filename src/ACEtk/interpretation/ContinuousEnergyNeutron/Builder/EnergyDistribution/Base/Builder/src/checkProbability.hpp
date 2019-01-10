double checkProbability( double probability ){
  if( probability < 0.0 ){
    Log::error( "Energy distribution probability must be >= 0.0" );
    Log::info( "Received probability: {}", probability );
    throw std::exception();
  }

  return probability;
}
