struct NeutronProducing{
  int MT;
  double Q;
  int neutronYield;
  ContinuousEnergyNeutron::Builder::CrossSection crossSection;
  std::variant< std::monostate,
                Isotropic, 
                AngularDistribution > angularDistribution;
  std::vector< EnergyDistribution > energyDistribution;
  std::optional< PhotonProduction > photonProduction;
  std::optional< Tabulated1D > energyDependentNeutronYields;
};
