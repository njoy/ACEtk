struct SimpleMaxwellianFissionSpectrum {

  Tabulated1D tabulatedEffectiveTemperature;
  double restrictionEnergy;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/SimpleMaxwellianFissionSpectrum/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/SimpleMaxwellianFissionSpectrum/src/ACEify.hpp"
};
