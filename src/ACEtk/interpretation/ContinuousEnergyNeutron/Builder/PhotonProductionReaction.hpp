struct PhotonProductionReaction {
  class Builder;


  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Yields.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/AngularDistribution.hpp"

  using MFType = std::variant< CrossSection, Yields >;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder.hpp"

  int MT;
  MFType crossSection;
  AngularDistribution angularDistribution;
  EnergyDistribution energyDistribution;
};
