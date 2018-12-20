struct TabularEquiprobableEnergyBins: 
  public ParentType::TabularEquiprobableEnergyBins {

  class Builder;
  using BaseBuilder = ContinuousEnergyNeutron::Builder::EnergyDistribution::
    TabularEquiprobableEnergyBins::Builder< 
      Builder,
      ContinuousEnergyNeutron::Builder::Reaction::EnergyDistribution::Builder >;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/EnergyDistribution/TabularEquiprobableEnergyBins/Builder.hpp"
};
