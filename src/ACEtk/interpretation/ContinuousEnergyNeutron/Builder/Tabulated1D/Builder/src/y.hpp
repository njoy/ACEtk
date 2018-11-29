Builder& y( std::vector< double>&& y ){
  this->y_ = std::move( y );
  return *this;
}
