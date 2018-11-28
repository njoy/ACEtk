Builder& multiplicities( std::vector< double>&& nubar ){
  this->multiplicities_ = std::move( nubar );
  return *this;
}

Builder& nubar( std::vector< double>&& nubar ){
  return this->multiplicities( std::move( nubar ) );
}
