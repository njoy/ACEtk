KalbachMannAngularDistribution construct() {
  this->y( std::move( data_ ) );

  return { TabBuilder::construct() };
}
