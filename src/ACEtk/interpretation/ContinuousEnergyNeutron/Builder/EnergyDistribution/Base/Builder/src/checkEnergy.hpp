double checkEnergy( double energy ){
  if( energy < 0.0 ){
    Log::error( "Energy distribution energy must be >= 0.0" );
    Log::info( "Received energy: {}", energy );
    throw std::exception();
  }

  return energy;
}
