ContinuousEnergyNeutron::Builder::PhotonProductionReaction::Builder&
addYields( ContinuousEnergyNeutron::Builder::Tabulated1D<>&& yields ){
  this->yields_ = std::move( yields );
  return *this;
}

