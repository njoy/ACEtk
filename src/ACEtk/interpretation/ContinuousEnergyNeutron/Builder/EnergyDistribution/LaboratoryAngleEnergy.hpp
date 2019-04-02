struct LaboratoryAngleEnergy {
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/AngularDistribution.hpp"

  Tabulated< AngularDistribution > tabulated;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/src/ACEify.hpp"
};
