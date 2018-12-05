PhotonProduction::Builder photonProduction( int MF, int MT ){
  if( not( ( MF == 12 ) or ( MF == 13 ) or ( MF == 16 ) ) ){
    Log::error( "Invalid photon production type: {}", MF );
    Log::info( "Valid photon production types are: 12, 13, and 16" );
    throw std::range_error( "invalid photon production type" );
  }
  return PhotonProduction::Builder( *this, MF, MT );
}
