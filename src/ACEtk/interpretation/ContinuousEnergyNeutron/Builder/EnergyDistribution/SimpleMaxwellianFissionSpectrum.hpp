struct SimpleMaxwellianFissionSpectrum {

  Tabulated1D tabulatedEffectiveTemperature;
  double restrictionEnergy;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/SimpleMaxwellianFissionSpectrum/Builder.hpp"
};