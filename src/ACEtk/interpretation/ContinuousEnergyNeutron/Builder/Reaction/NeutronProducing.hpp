struct NeutronProducing{
  int MT;
  double Q;
  int neutronYield;
  ContinuousEnergyNeutron::Builder::CrossSection crossSection;
  std::optional< AngularDistribution > angularDistribution;
  std::vector< EnergyDistribution > energyDistribution;
};
