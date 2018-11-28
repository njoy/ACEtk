class Builder {
 using ParentBuilder = 
     ContinuousEnergyNeutron::Builder::fissionMultiplicity::Builder;

  std::reference_wrapper< ParentBuilder > parent;
  std::optional< std::vector< double > > energies_;
  std::optional< std::vector< double > > multiplicities_;

protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/fissionMultiplicity/Tabulated/Builder/src/construct.hpp"

public:
  Builder( ParentBuilder& parent ):
    parent( parent )
  { }

  // ContinuousEnergyNeutron::Builder& add() { 
  //   return parent.get().addFissionNeutrons( this->construct() );
  // }
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/fissionMultiplicity/Tabulated/Builder/src/energies.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/fissionMultiplicity/Tabulated/Builder/src/multiplicities.hpp"
};

