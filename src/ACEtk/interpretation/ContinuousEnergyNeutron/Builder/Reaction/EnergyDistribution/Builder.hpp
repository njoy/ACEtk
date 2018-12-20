class Builder : 
  public ContinuousEnergyNeutron::Builder::EnergyDistribution::Builder<
    Builder, 
    EnergyDistribution,
    ContinuousEnergyNeutron::Builder::Reaction::Builder
  > {

  using ParentBuilder = ContinuousEnergyNeutron::Builder::Reaction::Builder;
  using BaseBuilder = ContinuousEnergyNeutron::Builder::EnergyDistribution::Builder<
    Builder, 
    EnergyDistribution,
    ContinuousEnergyNeutron::Builder::Reaction::Builder
  >;

protected:
  using BaseBuilder::construct;

public:
  using BaseBuilder::BaseBuilder;

  using BaseBuilder::boundaries;
  using BaseBuilder::schemes;
  using BaseBuilder::energies;
  using BaseBuilder::probabilities;

};
