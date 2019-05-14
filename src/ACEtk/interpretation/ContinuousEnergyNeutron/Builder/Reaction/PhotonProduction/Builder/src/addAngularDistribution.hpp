Builder&
addAngularDistribution( AngularDistribution&& angDist ){
  this->angularDistribution_ = std::move( angDist );
  return *this;
}
