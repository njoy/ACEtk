Builder& crossSection( std::vector< double >&& xs ){
  this->crossSection_ = std::move( xs );
  return *this;
}
