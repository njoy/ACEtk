struct EnergyDistributions {
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistributions/TabularEquiprobableEnergyBins.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistributions/ContinuousTabularDistribution.hpp"

  using LAWS = std::variant< TabularEquiprobableEnergyBins, // LAW=1
                             ContinuousTabularDistribution  // LAW=1
                           >;

};

