struct EnergyDependentWattSpectrum {

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Tabulated.hpp"

  Tabulated1D aTabulated;
  Tabulated1D bTabulated;
  double restrictionEnergy;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/src/ACEify.hpp"
};
