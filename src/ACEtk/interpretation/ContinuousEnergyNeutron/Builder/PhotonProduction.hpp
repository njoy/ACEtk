struct PhotonProduction {

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/Yields.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/CrossSection.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/Builder.hpp"
};

using PhotonReaction = std::variant< 
  Tabulated1D, PhotonProduction::CrossSection >;
