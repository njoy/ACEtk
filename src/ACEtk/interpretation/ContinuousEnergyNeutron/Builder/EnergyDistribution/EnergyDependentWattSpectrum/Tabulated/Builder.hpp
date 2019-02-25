template< typename ParentBuilder >
class Builder: public Tabulated1D::Builder< Builder< ParentBuilder > > {

  using BaseBuilder = Tabulated1D::Builder< Builder< ParentBuilder > >;

  std::reference_wrapper< ParentBuilder > parent;
  std::optional< Tabulated1D >& tabulated_;

public:
  Builder( ParentBuilder& parent, std::optional< Tabulated1D >& tabulated ):
    parent( parent ),
    tabulated_( tabulated )
  { }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Tabulated/Builder/src/add.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/EnergyDependentWattSpectrum/Tabulated/Builder/src/energies.hpp"

#define RENAME(basename, derivedname)\
  template< typename Range,\
            utility::Require< true, utility::is_range, Range > = true >\
  Builder& derivedname( Range&& derivedname ){\
    return BaseBuilder::basename( std::move( derivedname ) );\
  }

  RENAME( y, values )
#undef RENAME
};
