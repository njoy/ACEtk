class Builder: 
  public ContinuousEnergyNeutron::Builder::EnergyDistribution::
    TabularEquiprobableEnergyBins::Builder< 
      Builder,
      ContinuousEnergyNeutron::Builder::Reaction::EnergyDistribution::Builder 
    >{

  using BaseBuilder = ContinuousEnergyNeutron::Builder::EnergyDistribution::
    TabularEquiprobableEnergyBins::Builder< 
      Builder,
      ContinuousEnergyNeutron::Builder::Reaction::EnergyDistribution::Builder >;

public:
  using BaseBuilder::BaseBuilder;
};
