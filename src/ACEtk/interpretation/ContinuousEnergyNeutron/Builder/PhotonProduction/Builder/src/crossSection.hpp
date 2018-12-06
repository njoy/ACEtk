CrossSection::Builder crossSection(){
  if( this->MF != 13 ){
    Log::error( "Tabulated photon production only comes from MF=13" );
    throw std::range_error( "MF=13 must use cross section form" );
  }
  return CrossSection::Builder{ parent, this->MT }; 
}
