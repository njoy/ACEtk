Builder& neutronYieldReferenceFrame( NeutronYieldReferenceFrame frame ){
  if( not this->isNeutronProducing() ){
    Log::error( "Reaction: {} does not produce secondary neutrons." );
    Log::info( "Specified neutron yield reference frame will be ignored." );
  }
  this->neutronYieldReferenceFrame_ = frame;
  return *this;
}
