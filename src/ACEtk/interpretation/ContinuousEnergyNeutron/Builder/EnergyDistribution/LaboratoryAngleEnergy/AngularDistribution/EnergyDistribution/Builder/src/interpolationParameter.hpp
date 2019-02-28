Builder& interpolationParameter( int INTEP ){

  if( ( INTEP < 1 ) or ( INTEP > 2 ) ){
    Log::error( "Interpolation parameter (INTEP) must be 1 or 2, got: {}", 
                INTEP );
    throw std::exception();
  }

  this->interpolationParameter_ = INTEP;
  return *this;
}
