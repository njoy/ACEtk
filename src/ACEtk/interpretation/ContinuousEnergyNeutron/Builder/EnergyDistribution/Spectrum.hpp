template< typename S >
struct Spectrum {

  Tabulated1D tabulatedEffectiveTemperature;
  S spectrum;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Spectrum/Builder.hpp"
};
