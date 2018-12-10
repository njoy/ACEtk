struct Yields: protected ContinuousEnergyNeutron::Builder::Tabulated1D{

  using ParentBuilder = ContinuousEnergyNeutron::Builder;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/Yields/Builder.hpp"
};
