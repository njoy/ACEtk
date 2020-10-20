Builder& 
addEnergyDistribution( EnergyDistribution&& dist ){
  this->energyDistribution_.emplace_back( std::move( dist ) );
  return *this;
}
