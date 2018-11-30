struct Tabulated: protected ContinuousEnergyNeutron::Builder::Tabulated1D{

  using ParentBuilder = ContinuousEnergyNeutron::Builder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/fissionMultiplicity/Tabulated/Builder.hpp"
};
