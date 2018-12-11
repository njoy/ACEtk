ContinuousEnergyNeutron::Builder::PhotonProductionReaction::Builder&
addCrossSection( ContinuousEnergyNeutron::Builder::CrossSection&& XS ){
  this->crossSection_ = std::move( XS );
  return *this;
}
