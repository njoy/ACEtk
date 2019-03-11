ContinuousEnergyNeutron::Builder::PhotonProductionReaction::Builder& 
addEnergyDistribution( EnergyDistribution&& dist ){
  this->energyDistribution_ = std::move( dist );
  return *this;
}
