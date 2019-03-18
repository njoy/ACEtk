class Builder: public Tabulated1D::Builder< Builder >{

  using TabBuilder = Tabulated1D::Builder< Builder >;

  std::reference_wrapper< ParentBuilder > parent;
  std::optional< double > decayConstant_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Precursors/Builder/src/construct.hpp"

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  ParentBuilder& add(){
    return parent.get().addFissionMultiplicity( "precursors",
                                                this->construct() );
  }

  using TabBuilder::energies;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Precursors/Builder/src/probabilities.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity/Precursors/Builder/src/decayConstant.hpp"

};
