Builder& addElasticScattering( Reaction::NeutronProducing&& reaction ){
  this->elasticScattering_ = std::move( reaction );
  return *this;
}
