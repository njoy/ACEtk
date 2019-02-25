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

  template< typename Range,
            utility::Require< true, utility::is_range, Range > = true >
  Builder& equiprobableBins( Range&& bins ){
    this->equiprobableBins_ = std::move( bins );
    return *this;
  }

#define RENAME(basename, derivedname)\
  template< typename Range,\
            utility::Require< true, utility::is_range, Range > = true >\
  Builder& derivedname( Range&& derivedname ){\
    TabBuilder::basename( std::move( derivedname ) );\
    return *this;\
  }

  RENAME( y, effectiveTemperature )
#undef RENAME
};
