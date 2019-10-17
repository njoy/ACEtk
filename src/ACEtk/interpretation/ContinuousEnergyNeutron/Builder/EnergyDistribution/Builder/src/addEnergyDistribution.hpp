Builder& addEnergyDistribution( LAW&& law ){
  this->law_ = std::move( law );
  return *this;
}
