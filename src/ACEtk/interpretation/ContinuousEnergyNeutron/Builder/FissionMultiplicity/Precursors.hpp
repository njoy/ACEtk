struct Precursors {
  using ParentBuilder = ContinuousEnergyNeutron::Builder;

  double decayConstant;
  Tabulated1D data;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Precursors/Builder.hpp"
};
