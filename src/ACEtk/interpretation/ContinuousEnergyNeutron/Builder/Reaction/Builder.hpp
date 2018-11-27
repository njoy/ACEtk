class Builder{

private:
  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;
  std::optional< std::vector< double > > crossSection_;

protected:
  Reaction construct(){
    return Reaction{ std::move( this->crossSection_.value() ) };
  }

public:
  Builder( ContinuousEnergyNeutron::Builder& parent ):
    parent( parent )
  { }

  ContinuousEnergyNeutron::Builder& add() { 
    return parent.get().addReaction( this->construct() );
  }

  #include "ACEtk/interpretation/ContinuousEnergyNeutron/Builder/Reaction/Builder/src/crossSection.hpp"
};
