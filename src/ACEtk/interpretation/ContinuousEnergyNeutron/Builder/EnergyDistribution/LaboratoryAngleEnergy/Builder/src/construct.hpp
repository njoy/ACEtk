LaboratoryAngleEnergy construct() {
  this->y( std::move( angularDistributions_ ) );

  return { TabBuilder::construct() };
}
