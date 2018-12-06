struct PhotonProduction {

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/Tabulated.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/CrossSection.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/Builder.hpp"
  // using Builder = std::variant< Tabulated::Builder,
  //                               CrossSection::Builder >;
};

using PhotonReaction = std::variant< 
  Tabulated1D, PhotonProduction::CrossSection >;
