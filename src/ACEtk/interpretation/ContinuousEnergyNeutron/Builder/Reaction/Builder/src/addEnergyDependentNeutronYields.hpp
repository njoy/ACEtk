Builder& 
addEnergyDependentNeutronYields( Tabulated1D&& yields ){
  this->energyDependentNeutronYields_ = std::move( yields );
  return *this;
}
