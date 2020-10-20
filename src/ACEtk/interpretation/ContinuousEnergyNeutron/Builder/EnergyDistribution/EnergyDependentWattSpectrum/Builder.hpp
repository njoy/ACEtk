template< typename ParentBuilder >
class Builder: public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {

  using BaseBuilder = Base::Builder< Builder< ParentBuilder >, ParentBuilder >;

  std::optional< Tabulated1D > aTabulated_;
  std::optional< Tabulated1D > bTabulated_;
  std::optional< double > restrictionEnergy_;

protected:

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Builder/src/construct.hpp"

  friend Base::Builder< Builder< ParentBuilder >, ParentBuilder >;

public:
  using BaseBuilder::BaseBuilder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Builder/src/restrictionEnergy.hpp"

  Tabulated::Builder< Builder< ParentBuilder > >
  aTabulated(){ return { *this, aTabulated_ }; }
  Tabulated::Builder< Builder< ParentBuilder > >
  bTabulated(){ return { *this, bTabulated_ }; }


};
