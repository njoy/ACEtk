struct CrossSection{

  int MF;
  ContinuousEnergyNeutron::Builder::CrossSection data;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/CrossSection/src/ACEify.hpp"
};
