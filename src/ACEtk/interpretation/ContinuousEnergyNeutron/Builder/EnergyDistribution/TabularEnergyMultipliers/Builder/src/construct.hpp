TabularEnergyMultipliers construct(){
  this->y( std::move( tables_ ) );

  return TabBuilder::construct();
}
