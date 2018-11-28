class Builder {
  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;

protected:
  Reaction construct(){
    return FissionNeutrons{};
  }

public:
  Builder( int MT, ContinuousEnergyNeutron::Builder& parent ):
    parent( parent ), MT_( MT )
  { }

  ContinuousEnergyNeutron::Builder& add() { 
    return parent.get().addReaction( this->construct() );
  }

};
