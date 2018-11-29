class Builder{
protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Tabulated1D.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionMultiplicity.hpp"

  std::optional< std::vector< double > > energyGrid_;
  // std::optional< FissionMultiplicity > fissionMultiplicity_;
  tsl::hopscotch_map< int, Reaction > reactions_;

  friend Reaction::Builder;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addReaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addFissionMultiplicity.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/energyGrid.hpp"
  Reaction::Builder reaction( int MT ){ return Reaction::Builder{ MT, *this }; }
  fissionMultiplicity::Builder fissionMultiplicity() { 
    return fissionMultiplicity::Builder{ *this }; 
  }

};
