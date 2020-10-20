Builder& addEnergyDistribution( EnergyDistribution&& eng ){
  energyDistributions_.emplace_back( std::move( eng ) );
  return *this;
}

