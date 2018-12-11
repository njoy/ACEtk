template< typename Derived, typename ParentBuilder >
class Builder{

public:
  std::optional< details::verify::Positive< std::vector< double > > > values_;
  std::optional< Table::Slice > energyGrid_;

protected:
  std::reference_wrapper< ParentBuilder > parent;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder/src/construct.hpp"

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder/src/values.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder/src/energyGrid.hpp"
};
