Builder& interpolationParameter( int INTMU ){

  if( ( INTMU < 1 ) or ( INTMU > 2 ) ){
    Log::error( "Interpolation parameter (INTMU) must be 1 or 2, got: {}", 
                INTMU );
    throw std::exception();
  }

  this->interpolationParameter_ = INTMU;
  return *this;
}
