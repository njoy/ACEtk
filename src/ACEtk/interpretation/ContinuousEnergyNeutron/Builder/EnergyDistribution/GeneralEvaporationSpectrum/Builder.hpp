template< typename ParentBuilder >
class Builder:
  public Tabulated1D::Builder< Builder< ParentBuilder > >,
  public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {

  using BaseBuilder = Base::Builder< Builder< ParentBuilder >, ParentBuilder >;
  using TabBuilder = Tabulated1D::Builder< Builder< ParentBuilder > >;

  std::optional< std::vector< double > > equiprobableBins_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum/Builder/src/construct.hpp"

  friend Base::Builder< Builder< ParentBuilder >, ParentBuilder >;

public:
  using BaseBuilder::BaseBuilder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum/Builder/src/energies.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum/Builder/src/effectiveTemperature.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/GeneralEvaporationSpectrum/Builder/src/equiprobableBins.hpp"
};
