template< typename ParentBuilder >
class Builder:
  public Tabulated1D::Builder< Builder< ParentBuilder > >,
  public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {

  using BaseBuilder = Base::Builder< Builder< ParentBuilder >, ParentBuilder >;
  using TabBuilder = Tabulated1D::Builder< Builder< ParentBuilder > >;

  std::optional< double > restrictionEnergy_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EvaporationSpectrum/Builder/src/construct.hpp"

  friend Base::Builder< Builder< ParentBuilder >, ParentBuilder >;

public:
  using BaseBuilder::BaseBuilder;

  using TabBuilder::energies;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EvaporationSpectrum/Builder/src/effectiveTemperature.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EvaporationSpectrum/Builder/src/restrictionEnergy.hpp"
};
