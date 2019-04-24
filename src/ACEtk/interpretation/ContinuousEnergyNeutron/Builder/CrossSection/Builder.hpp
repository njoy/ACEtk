template< typename ParentBuilder >
class Builder{

public:
  std::optional< dvP< std::vector< double > > > values_;
  std::optional< Table::pizza > energyGrid_;

protected:
  std::reference_wrapper< ParentBuilder > parent;

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder/src/construct.hpp"

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add(){
    return parent.get().addCrossSection( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder/src/values.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/CrossSection/Builder/src/energyGrid.hpp"
};
