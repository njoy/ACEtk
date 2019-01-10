Builder& addEnergyDistribution( double energy, double probability, LAWS&& law ){
  energies_.emplace_back( energy );
  probabilities_.emplace_back( probability );
  laws_.emplace_back( std::move( law ) );
  return *this;
}
