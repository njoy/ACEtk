Builder& addFissionNeutrons( FissionNeutrons&& nubar ){
  if( this->fissionNeutrons_ ){
    njoy::Log::error( "Fission neutrons (nubar) has already been defined." );
    throw std::exception();
  }

  this->fissionNeutrons_ = std::move( nubar );
  return *this;
}
