Builder& addData( AngularDistribution&& data ){
  angularDistributions_.emplace_back( std::move( data ) );
  return *this;
}
