template< typename ParentBuilder >
class Builder: 
  public Tabulated< AngularDistribution >::Builder< Builder< ParentBuilder > >,
  public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {

  using TabBuilder = 
      Tabulated< AngularDistribution >::Builder< Builder< ParentBuilder > >;
  using BaseBuilder = Base::Builder< Builder< ParentBuilder >, ParentBuilder >;

  std::vector< AngularDistribution > angularDistributions_;

protected:

  using TabBuilder::y;

  friend Base::Builder< Builder< ParentBuilder >, ParentBuilder >;
  friend AngularDistribution::Builder< Builder< ParentBuilder > >;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/Builder/src/construct.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/Builder/src/addAngularDistribution.hpp"

public:
  using BaseBuilder::BaseBuilder;

  AngularDistribution::Builder< Builder< ParentBuilder > > angularDistribution(){
    return { *this };
  }
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LaboratoryAngleEnergy/Builder/src/energies.hpp"
};
