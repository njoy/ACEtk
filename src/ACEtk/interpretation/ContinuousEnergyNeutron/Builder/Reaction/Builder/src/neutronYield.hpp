Builder& neutronYield( int y ){
  if( not this->isNeutronProducing() ){
    Log::error( "Reaction: {} does not produce secondary neutrons." );
    Log::info( "Specified neutron yield will be ignored." );
  }

  try{
    details::verify::neutronYield( y );

  } catch( details::verify::exceptions::InvalidNeutronYield& e ){
    Log::info( "Invalid neutron yield." );
    throw;
  }

  this->neutronYield_ = y;
  return *this;
}
