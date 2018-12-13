Builder& interpolationParameter( int iP ){
  if( ( iP != 2 ) and ( iP != 5 ) ){
    Log::error( "Invald interpolation parameter: {}", iP );
    Log::info( "Interpolation parameter between unresolved resonance tables "
               " must be 2 or 5" );
    throw std::range_error( "Invalid interpolation parameter" );
  }

  this->interpolationParameter_ = iP;
  return *this;
}
