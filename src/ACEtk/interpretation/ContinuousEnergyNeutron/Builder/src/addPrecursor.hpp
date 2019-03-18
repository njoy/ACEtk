Builder& addPrecursor( Precursors&& p ){
  this->delayedPrecursors_.emplace_back( std::move( p ) );
  return *this;
}
