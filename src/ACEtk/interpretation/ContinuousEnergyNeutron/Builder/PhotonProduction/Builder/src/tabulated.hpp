Tabulated::Builder tabulated(){ 
  if( this->MF == 13 ){
    Log::error( "Tabulated photon production only comes from MF=12 or MF=16" );
    throw std::range_error( "MF=13 must use cross section form" );
  }
  return Tabulated::Builder{ parent, this->MT }; 
}
