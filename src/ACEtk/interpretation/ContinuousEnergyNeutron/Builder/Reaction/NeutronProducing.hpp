struct NeutronProducing{
  int MT;
  double Q;
  int neutronYield;
  NeutronYieldReferenceFrame neutronYieldReferenceFrame;
  ContinuousEnergyNeutron::Builder::CrossSection crossSection;
  std::variant< std::monostate,
                Isotropic, 
                AngularDistribution > angularDistribution;
  std::vector< EnergyDistribution > energyDistribution;
  std::optional< PhotonProduction > photonProduction;
  std::optional< EnergyDependentNeutronYields > edNeutronYields;
};
