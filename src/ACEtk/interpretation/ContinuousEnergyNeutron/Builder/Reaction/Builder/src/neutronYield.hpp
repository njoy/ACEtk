Builder& neutronYield( int y, NeutronYieldReferenceFrame frame ){
  try{
    details::verify::neutronYield( y );
  } catch( details::verify::exceptions::InvalidNeutronYield& e ){
    Log::info( "Invalid neutron yield." );
    throw;
  }

  this->neutronYield_ = y;
  this->neutronYieldReferenceFrame_ = frame;
  return *this;
}
