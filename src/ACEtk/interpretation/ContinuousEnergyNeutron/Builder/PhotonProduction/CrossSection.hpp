struct CrossSection: protected ContinuousEnergyNeutron::Builder::CrossSection {

  using ParentBuilder = ContinuousEnergyNeutron::Builder;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/CrossSection/Builder.hpp"
};
