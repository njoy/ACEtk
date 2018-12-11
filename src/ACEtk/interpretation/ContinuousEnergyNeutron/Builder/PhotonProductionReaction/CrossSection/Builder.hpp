class Builder:
  public ContinuousEnergyNeutron::Builder::CrossSection::Builder< 
    Builder,
    ContinuousEnergyNeutron::Builder::PhotonProductionReaction::Builder
  > {

  using ParentBuilder = ContinuousEnergyNeutron::Builder::
      PhotonProductionReaction::Builder;
  using BaseBuilder = ContinuousEnergyNeutron::Builder::
    CrossSection::Builder< Builder, ParentBuilder >;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/PhotonProductionReaction/CrossSection/Builder/src/construct.hpp"

public:

  ParentBuilder& add(){
    return parent.get().addCrossSection( this->construct() );
  }
  using BaseBuilder::BaseBuilder;
  using BaseBuilder::energyGrid;
  using BaseBuilder::values;
};
