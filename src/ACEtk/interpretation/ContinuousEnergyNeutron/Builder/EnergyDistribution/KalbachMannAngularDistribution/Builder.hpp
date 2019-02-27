template< typename ParentBuilder >
class Builder: 
  public Tabulated< Data >::Builder< Builder< ParentBuilder > >,
  public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {

  using TabBuilder = Tabulated< Data >::Builder< Builder< ParentBuilder > >;
  using BaseBuilder = Base::Builder< Builder< ParentBuilder >, ParentBuilder >;

  std::vector< Data > data_;

protected:

  using TabBuilder::y;

  friend Base::Builder< Builder< ParentBuilder >, ParentBuilder >;
  friend Data::Builder< Builder< ParentBuilder > >;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Builder/src/construct.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Builder/src/addData.hpp"

public:
  using BaseBuilder::BaseBuilder;

  Data::Builder< Builder< ParentBuilder > > distributionData(){
    return { *this };
  }
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/KalbachMannAngularDistribution/Builder/src/energies.hpp"
};

