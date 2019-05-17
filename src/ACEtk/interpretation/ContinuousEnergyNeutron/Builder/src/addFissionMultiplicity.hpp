Builder& addFissionMultiplicity( std::string nuType, Nubar&& nubar){
  this->fissionMultiplicity_[ nuType ] = std::move( nubar );
  return *this;
}
