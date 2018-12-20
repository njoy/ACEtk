struct EnergyDistribution: 
    protected ContinuousEnergyNeutron::Builder::EnergyDistribution {

  class Builder;
  using ParentType = ContinuousEnergyNeutron::Builder::EnergyDistribution;
  using ParentBuilder = 
      ContinuousEnergyNeutron::Builder::Reaction::EnergyDistribution::Builder;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/EnergyDistribution/TabularEquiprobableEnergyBins.hpp"

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/EnergyDistribution/Builder.hpp"
};
