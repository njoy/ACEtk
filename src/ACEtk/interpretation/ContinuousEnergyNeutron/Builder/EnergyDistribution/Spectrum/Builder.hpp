template< typename Derived, typename ParentBuilder >
class Builder: 
  public Tabulated1D::Builder< Builder< Derived, ParentBuilder > >,
  public Base::Builder< Builder< Derived, ParentBuilder >, ParentBuilder > {

  using BaseBuilder = 
      Base::Builder< Builder< Derived, ParentBuilder >, ParentBuilder >;

protected:
  using TabBuilder = Tabulated1D::Builder< Builder< Derived, ParentBuilder > >;
  std::optional< S > spectrum_;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Spectrum/Builder/src/construct.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Spectrum/Builder/src/spectrum.hpp"

  friend Base::Builder< Builder< Derived, ParentBuilder >, ParentBuilder >;

public:
  using BaseBuilder::BaseBuilder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Spectrum/Builder/src/energies.hpp"

#define RENAME(basename, derivedname)\
  template< typename Range,\
            utility::Require< true, utility::is_range, Range > = true >\
  Derived& derivedname( Range&& derivedname ){\
    TabBuilder::basename( std::move( derivedname ) );\
    return static_cast< Derived& >( *this );\
  }

  RENAME( y, effectiveTemperature )
#undef RENAME
};
