struct GeneralEvaporationSpectrum {

  Tabulated1D tabulatedEffectiveTemperature;
  std::vector< double > equiprobableBins;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum/src/ACEify.hpp"
};
