class Builder {
  std::reference_wrapper< ContinuousEnergyNeutron::Builder > parent;

protected:
  FissionNeutrons construct(){
    return FissionNeutrons{};
  }

public:
  Builder( ContinuousEnergyNeutron::Builder& parent ):
    parent( parent )
  { }

  ContinuousEnergyNeutron::Builder& add() { 
    return parent.get().addFissionNeutrons( this->construct() );
  }

};
