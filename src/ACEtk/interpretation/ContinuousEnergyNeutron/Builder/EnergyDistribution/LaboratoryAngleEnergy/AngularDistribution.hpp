struct AngularDistribution {
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/EnergyDistribution.hpp"

  int interpolationParameter;
  std::vector< double > cosines;
  std::vector< EnergyDistribution > energyDistributions;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution/Builder.hpp"
};