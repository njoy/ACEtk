CrossSection::Builder crossSection(){
  if( this->MF != 13 ){
    Log::error( "Photon production cross section only comes from MF=13" );
    throw std::range_error( "MF=12,16 must use photon production yields" );
  }
  return CrossSection::Builder{ parent, this->MT }; 
}
