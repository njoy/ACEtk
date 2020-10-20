template< typename ParentBuilder >
class Builder: 
  public Tabulated< dvP< std::vector< double > > >::
    Builder< Builder< ParentBuilder > >,
  public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {


  using TabBuilder = Tabulated< 
    dvP< std::vector< double > > >::Builder< 
      Builder< ParentBuilder > >;
  using BaseBuilder = Base::Builder< Builder< ParentBuilder >, ParentBuilder >;

  std::vector< dvP< std::vector< double > > > tables_;

protected:

  using TabBuilder::y;

  friend Base::Builder< Builder< ParentBuilder >, ParentBuilder >;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEnergyMultipliers/Builder/src/construct.hpp"

public:
  using BaseBuilder::BaseBuilder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEnergyMultipliers/Builder/src/table.hpp"
  using TabBuilder::energies;

};
