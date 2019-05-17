Builder& 
addEnergyDependentNeutronYields( EnergyDependentNeutronYields&& yields ){
  this->energyDependentNeutronYields_ = std::move( yields );
  return *this;
}
