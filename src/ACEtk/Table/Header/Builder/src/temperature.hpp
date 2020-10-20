Builder& temperature( Quantity< Mega< ElectronVolts > > temp ){
  if( temp < 0.0*mega( electronVolts ) ){
    Log::error( "Temperature must be positive" );
    Log::info( "Given temperature of: {}", temp );
    throw std::exception();
  }

  this->processTemperature_ = temp;
  return *this;
}

Builder& temperature( double temp ){
  return this->temperature( temp*mega( electronVolts ) );
}
