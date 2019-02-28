template< typename ParentBuilder >
class Builder: 
  public Tabulated< details::verify::Positive< std::vector< double > > >::
    Builder< Builder< ParentBuilder > >,
  public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {


  using TabBuilder = Tabulated< 
    details::verify::Positive< std::vector< double > > >::Builder< 
      Builder< ParentBuilder > >;
  using BaseBuilder = Base::Builder< Builder< ParentBuilder >, ParentBuilder >;

  std::vector< details::verify::Positive< std::vector< double > > > tables_;

protected:

  using TabBuilder::y;

  friend Base::Builder< Builder< ParentBuilder >, ParentBuilder >;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LAW24/Builder/src/construct.hpp"

public:
  using BaseBuilder::BaseBuilder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LAW24/Builder/src/table.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/LAW24/Builder/src/energies.hpp"

};
