template< typename ParentBuilder >
class Builder: public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {
  using BaseBuilder = Base::Builder< Builder, ParentBuilder >;

  friend class Base::Builder< Builder, ParentBuilder >;

  std::optional< double > atomicWeightRatio_;
  std::optional< double > QValue_;

protected:
  LevelScattering construct(){
    return { atomicWeightRatio_.value(), QValue_.value() };
  }

public:

  using BaseBuilder::BaseBuilder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LevelScattering/Builder/src/atomicWeightRatio.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LevelScattering/Builder/src/QValue.hpp"
};
