struct PhotonProductionReaction {
  class Builder;

  using MFType = std::variant< CrossSection, Tabulated1D >;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Yields.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/AngularDistribution.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder.hpp"

  int MT;
  MFType crossSection;
  AngularDistribution angularDistribution;
  EnergyDistribution energyDistribution;
};
