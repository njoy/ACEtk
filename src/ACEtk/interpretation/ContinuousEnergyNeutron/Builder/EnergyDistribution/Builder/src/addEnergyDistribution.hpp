Builder& addEnergyDistribution( LAWS&& law ){
  laws_.emplace_back( std::move( law ) );
  return *this;
}
