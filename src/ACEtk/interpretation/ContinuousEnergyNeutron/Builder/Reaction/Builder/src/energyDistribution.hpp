EnergyDistribution::Builder< Builder > energyDistribution(){ 
  if( this->isNeutronProducing() ){
    return EnergyDistribution::Builder< Builder >{ *this }; 
  } else {
    Log::error( "Reaction: {} does not produce secondary neutrons." );
    Log::info( "Must not specify energy distribution." );
    throw std::range_error( "Energy distribution not allowed." );
  }
}
