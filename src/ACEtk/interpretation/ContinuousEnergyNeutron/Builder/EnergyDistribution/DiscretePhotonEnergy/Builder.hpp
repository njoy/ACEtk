template< typename ParentBuilder >
class Builder: public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {
  using BaseBuilder = Base::Builder< Builder, ParentBuilder >;

  std::optional< int > primaryFlag_;
  std::optional< double > energy_;

  friend class Base::Builder< Builder, ParentBuilder >;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/DiscretePhotonEnergy/Builder/src/construct.hpp"

public:

  using BaseBuilder::BaseBuilder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/DiscretePhotonEnergy/Builder/src/energy.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/DiscretePhotonEnergy/Builder/src/primaryFlag.hpp"
};
