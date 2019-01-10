template< typename ParentBuilder >
class Builder: 
  public Tabulated< details::verify::Positive< std::vector< double > > >::
    Builder< Builder< ParentBuilder > >,
  public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {


  using TabBuilder = Tabulated< 
    details::verify::Positive< std::vector< double > > >::Builder< 
      Builder< ParentBuilder > >;
  using BaseBuilder = Base::Builder< Builder< ParentBuilder >, ParentBuilder >;

  std::vector< details::verify::Positive< 
      std::vector< double > > > outgoingEnergyTables_;

protected:

  using TabBuilder::x;
  using TabBuilder::y;

public:
  using BaseBuilder::BaseBuilder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEquiprobableEnergyBins/Builder/src/outgoingEnergyTable.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/TabularEquiprobableEnergyBins/Builder/src/construct.hpp"

#define RENAME(basename, derivedname)\
  template< typename Range,\
            utility::Require< true, utility::is_range, Range > = true >\
  Builder& derivedname( Range&& derivedname ){\
    return TabBuilder::basename( std::move( derivedname ) );\
  }

  RENAME( x, energies )
#undef RENAME
};
