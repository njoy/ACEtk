struct CrossSection: protected ContinuousEnergyNeutron::Builder::CrossSection {

  // using ParentBuilder = ContinuousEnergyNeutron::Builder::Reaction::Builder;

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/CrossSection/Builder.hpp"
};

