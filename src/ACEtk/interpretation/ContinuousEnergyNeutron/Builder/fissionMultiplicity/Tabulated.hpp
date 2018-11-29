struct Tabulated: protected ContinuousEnergyNeutron::Builder::Tabulated1D{

  using ParentBuilder = ContinuousEnergyNeutron::Builder;
  using BaseBuilder = 
      ContinuousEnergyNeutron::Builder::Tabulated1D::Builder< ParentBuilder >;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/fissionMultiplicity/Tabulated/Builder.hpp"
};
