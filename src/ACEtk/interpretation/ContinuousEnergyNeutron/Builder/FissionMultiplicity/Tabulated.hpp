struct Tabulated: protected ContinuousEnergyNeutron::Builder::Tabulated1D<>{

  using ParentBuilder = ContinuousEnergyNeutron::Builder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Tabulated/Builder.hpp"
};
