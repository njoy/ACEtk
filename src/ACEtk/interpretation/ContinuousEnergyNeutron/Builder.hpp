class Builder{
protected:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction.hpp"

  tsl::hopscotch_map< int, Reaction > reactions_;
  std::optional< std::vector< double > > energyGrid_;

  friend Reaction::Builder;
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/addReaction.hpp"

public:
  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/src/energyGrid.hpp"
  Reaction::Builder reaction( int MT ){ return Reaction::Builder{ MT, *this }; }

};
