template< typename ParentBuilder >
class Builder: public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {
  using BaseBuilder = Base::Builder< Builder, ParentBuilder >;

  std::optional< int > numberBodies_;
  std::optional< double > totalMassRatio_;

  friend class Base::Builder< Builder, ParentBuilder >;

protected:
  NBodyPhaseSpace construct(){
    return { numberBodies_.value(), totalMassRatio_.value() };
  }

public:

  using BaseBuilder::BaseBuilder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/NBodyPhaseSpace/Builder/src/numberBodies.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/NBodyPhaseSpace/Builder/src/totalMassRatio.hpp"
};
