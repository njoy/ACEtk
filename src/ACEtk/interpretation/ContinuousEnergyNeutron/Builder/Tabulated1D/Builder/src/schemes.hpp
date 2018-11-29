Builder& schemes( std::vector< double>&& schemes ){
  this->schemes_ = std::move( schemes );
  return *this;
}
