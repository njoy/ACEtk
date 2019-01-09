template< typename ParentBuilder >
class Builder: public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {
  using BaseBuilder = Base::Builder< Builder, ParentBuilder >;

  friend class Base::Builder< Builder, ParentBuilder >;

  std::optional< std::array< double, 2 > > LDAT_;

protected:
  LevelScattering construct(){
    return { LDAT_.value() };
  }

public:

  using BaseBuilder::BaseBuilder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LevelScattering/Builder/src/LDAT.hpp"
};
