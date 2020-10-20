ContinuousEnergyNeutron::Builder::Reaction::Builder& 
addCrossSection( CrossSection&& XS ){
  this->crossSection_ = std::move( XS );
  return *this;
}
