struct PhotonProductionReaction {
  class Builder;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Yields.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/CrossSection.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/AngularDistribution.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/Builder.hpp"

  int MT;
  std::optional< ContinuousEnergyNeutron::Builder::Tabulated1D > yields;
  std::optional< ContinuousEnergyNeutron::Builder::CrossSection > crossSection;
  AngularDistribution angularDistribution;

};
