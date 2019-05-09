Yields::Builder yields(){ 
  if( this->MF == 13 ){
    Log::error( "Photon production yields only come from MF=12 or MF=16" );
    throw std::range_error( "MF=13 must use cross section form" );
  }
  return Yields::Builder{ *this, this->MF, this->MT }; 
}
