struct PhotonProduction {
  class Builder;


  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/CrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/Yields.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/AngularDistribution.hpp"

  using MFType = std::variant< CrossSection, Yields >;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/PhotonProduction/Builder.hpp"

  int MT;
  MFType crossSection;
  AngularDistribution angularDistribution;
  std::vector< EnergyDistribution > energyDistribution;
};
