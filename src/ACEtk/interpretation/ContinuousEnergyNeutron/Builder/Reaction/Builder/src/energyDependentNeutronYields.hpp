EnergyDependentNeutronYields::Builder
energyDependentNeutronYields(){
  if( not this->isNeutronProducing() ){
    Log::error( "Reaction: {} does not produce secondary neutrons." );
    Log::info( "Specified energy-dependent neutron yields will be ignored." );
  }
  return EnergyDependentNeutronYields::Builder{ *this };
}
