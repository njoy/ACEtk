class Builder{
protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/FissionNeutrons.hpp"

  std::optional< std::vector< double > > energyGrid_;
  std::optional< FissionNeutrons > fissionNeutrons_;
  tsl::hopscotch_map< int, Reaction > reactions_;

  friend Reaction::Builder;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addReaction.hpp"
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addFissionNeutrons.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/energyGrid.hpp"
  Reaction::Builder reaction( int MT ){ return Reaction::Builder{ MT, *this }; }
  FissionNeutrons::Builder fissionNeutrons( ){ 
    return FissionNeutrons::Builder{ *this }; }
  FissionNeutrons::Builder nubar( ){ return fissionNeutrons(); }


};
