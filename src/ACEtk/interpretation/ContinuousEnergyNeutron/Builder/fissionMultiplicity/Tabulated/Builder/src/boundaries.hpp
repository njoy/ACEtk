Builder& boundaries( std::vector< double>&& boundaries ){
  this->boundaries_ = std::move( boundaries );
  return *this;
}
