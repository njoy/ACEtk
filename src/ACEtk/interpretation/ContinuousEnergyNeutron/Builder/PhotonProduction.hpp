struct PhotonProduction {
  class Builder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/Tabulated.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProduction/Builder.hpp"
};

using PhotonReaction = std::variant< Tabulated1D >;
