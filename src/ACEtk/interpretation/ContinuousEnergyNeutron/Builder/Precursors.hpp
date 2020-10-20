struct Precursors {
  using ParentBuilder = ContinuousEnergyNeutron::Builder;

  double decayConstant;
  Tabulated1D data;
  std::vector< EnergyDistribution > energyDistribution;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Precursors/Builder.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Precursors/src/ACEify.hpp"

};
