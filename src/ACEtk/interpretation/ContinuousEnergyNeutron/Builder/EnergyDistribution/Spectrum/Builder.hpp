template< typename ParentBuilder >
class Builder: 
  public Tabulated1D::Builder< Builder< ParentBuilder > >,
  public Base::Builder< Builder< ParentBuilder >, ParentBuilder > {

  using TabBuilder = Tabulated1D::Builder< Builder< ParentBuilder > >;
  using BaseBuilder = Base::Builder< Builder< ParentBuilder >, ParentBuilder >;

  std::optional< S > spectrum_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Spectrum/Builder/src/construct.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Spectrum/Builder/src/spectrum.hpp"

public:
  using BaseBuilder::BaseBuilder;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/EnergyDistribution/Spectrum/Builder/src/energies.hpp"

#define RENAME(basename, derivedname)\
  template< typename Range,\
            utility::Require< true, utility::is_range, Range > = true >\
  Builder& derivedname( Range&& derivedname ){\
    return TabBuilder::basename( std::move( derivedname ) );\
  }

  RENAME( y, effectiveTemperature )
#undef RENAME
};
