struct EvaporationSpectrum {

  Tabulated1D tabulatedEffectiveTemperature;
  double restrictionEnergy;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EvaporationSpectrum/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EvaporationSpectrum/src/ACEify.hpp"
};
