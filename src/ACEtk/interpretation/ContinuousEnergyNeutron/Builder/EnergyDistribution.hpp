struct EnergyDistribution : 
  protected ContinuousEnergyNeutron::Builder::Tabulated1D {

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEquiprobableEnergyBins.hpp"
  
  // std::vectro< LAW > laws_;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Builder.hpp"
};
