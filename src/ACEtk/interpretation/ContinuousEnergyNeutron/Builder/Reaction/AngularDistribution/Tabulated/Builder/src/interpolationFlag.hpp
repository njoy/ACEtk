Builder& interpolationFlag( int f ){
  if( ( f !=0 ) and ( f != 1 ) ){
    Log::error( "invalid interpolation flag for angular distribution" );
    Log::info( "valid interpolation flag values are 0 and 1" );
    throw std::exception();
  }
  this->interpolationFlag_ = f;
  return *this;
}
