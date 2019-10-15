Builder& interpolationParameter( int INTT ){
  if( ( INTT < 1 ) or ( INTT > 2 ) ){
    Log::error( "Interpolation parameter must either 1 or 2." );
    Log::info( "Given value of {}", INTT );
    throw std::exception();
  }

  this->interpolationParameter_ = INTT;
  return *this;
}
