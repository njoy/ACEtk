Builder& decayConstant( double lambda ){
  if( lambda < 0.0 ){
    Log::error( "Delayed nubar precursor decay constant must be >= 0.0." );
    Log::info( "Decay constant: {}", lambda );
    throw std::exception();
  }

  this->decayConstant_ = lambda;
  return *this;
}
