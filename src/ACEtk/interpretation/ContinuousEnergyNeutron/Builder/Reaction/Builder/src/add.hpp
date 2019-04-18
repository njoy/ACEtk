ContinuousEnergyNeutron::Builder& add() { 
  if( this->MT_ == 2 ){
    return parent.get().addElasticScattering( 
        this->constructNeutronProducing() );
  }
  if( this->isNeutronProducing() ){
    return parent.get().addReaction( this->constructNeutronProducing() );
  } else{
    return parent.get().addReaction( this->constructNonNeutronProducing() );
  }
}
