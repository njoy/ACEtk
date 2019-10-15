Builder& interpolationParameter( int JJ ){
  if( ( JJ < 1 ) or ( JJ > 2 ) ){
    Log::error( "Interpolation parameter must either 1 or 2." );
    Log::info( "Given value of {}", JJ );
    throw std::exception();
  }

  this->interpolationParameter_ = JJ;
  return *this;
}
