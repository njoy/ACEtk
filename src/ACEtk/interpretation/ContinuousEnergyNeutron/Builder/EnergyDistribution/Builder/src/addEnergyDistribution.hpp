Builder& addEnergyDistribution(  LAWS&& law ){
  this->law_ = std::move( law );
  return *this;
}
