ContinuousEnergyNeutron::Builder::Reaction::Builder& 
addCrossSection( ContinuousEnergyNeutron::Builder::CrossSection&& XS ){
  this->crossSection_ = std::move( XS );
  return *this;
}
