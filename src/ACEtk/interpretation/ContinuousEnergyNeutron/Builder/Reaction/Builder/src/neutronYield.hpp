Builder& neutronYield( int y, NeutronYieldReferenceFrame frame ){
  try{
    details::verify::neutronYield( y );

    if( ( y == 0 ) and ( this->MT_ <= 100 ) and ( this->MT_ != 2 ) ){
      Log::error( "Neutron yield must be > 0 for MTs <= 100" );
      throw std::exception();
    }
  } catch( details::verify::exceptions::InvalidNeutronYield& e ){
    Log::info( "Invalid neutron yield." );
    throw;
  }

  this->neutronYield_ = y;
  this->neutronYieldReferenceFrame_ = frame;
  return *this;
}
