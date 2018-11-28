class Builder{

private:
  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;
  int MT_;
  std::optional< std::vector< double > > crossSection_;
  std::optional< Table::Slice > energyGrid_;

protected:
  Reaction construct(){
    return Reaction{ 
      MT_, 
      energyGrid_.value(),
      std::move( this->crossSection_.value() ) };
  }

public:
  Builder( int MT, ContinuousEnergyNeutron::Builder& parent ):
    parent( parent ), MT_( MT )
  { }

  ContinuousEnergyNeutron::Builder& add() { 
    return parent.get().addReaction( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/crossSection.hpp"
};
