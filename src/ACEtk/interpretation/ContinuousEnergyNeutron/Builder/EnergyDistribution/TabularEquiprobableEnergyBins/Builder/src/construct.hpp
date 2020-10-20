TabularEquiprobableEnergyBins construct(){
  this->y( std::move( outgoingEnergyTables_ ) );

  return TabBuilder::construct();
}
