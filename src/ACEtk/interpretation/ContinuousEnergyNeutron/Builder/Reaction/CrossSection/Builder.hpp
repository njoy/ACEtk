class Builder:
  public ContinuousEnergyNeutron::Builder::CrossSection::Builder< 
    Builder, 
    ContinuousEnergyNeutron::Builder::Reaction::Builder
  > {

  using ParentBuilder = ContinuousEnergyNeutron::Builder::Reaction::Builder;
  using BaseBuilder = ContinuousEnergyNeutron::Builder::
    CrossSection::Builder< Builder, ParentBuilder >;

public:

  ParentBuilder& add(){
    return parent.get().addCrossSection( this->construct() );
  }

  using BaseBuilder::BaseBuilder;
  using BaseBuilder::energyGrid;
  using BaseBuilder::values;
};
