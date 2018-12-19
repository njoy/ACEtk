ContinuousEnergyNeutron::Builder::Reaction::Builder& 
addAngularDistribution( AngularDistribution&& dist ){
  this->angularDistribution_ = std::move( dist );
  return *this;
}

