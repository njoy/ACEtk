Builder& isotropic(){
  this->angularDistribution_ = Isotropic{};
  return *this;
}
