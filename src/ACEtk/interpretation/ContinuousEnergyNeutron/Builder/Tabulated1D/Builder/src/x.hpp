Builder& x( std::vector< double>&& x ){
  this->x_ = std::move( x );
  return *this;
}
