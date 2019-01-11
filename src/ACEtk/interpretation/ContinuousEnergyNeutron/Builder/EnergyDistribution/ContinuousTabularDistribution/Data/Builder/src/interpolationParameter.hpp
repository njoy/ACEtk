Builder& interpolationParameter( int interpolationParameter ){
  if( interpolationParameter < 0 ){
    Log::error( "Interpolation parameter must be greater than 0" );
    throw std::exception();
  }

  this->interpolationParameter_ = interpolationParameter;
  return *this;
}

