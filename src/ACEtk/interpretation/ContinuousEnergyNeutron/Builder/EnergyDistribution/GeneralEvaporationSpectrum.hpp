struct GeneralEvaporationSpectrum {

  Tabulated1D tabulatedEffectiveTemperature;
  std::vector< double > x;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum/Builder.hpp"
};