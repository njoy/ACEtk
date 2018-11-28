Builder& energies( std::vector< double>&& energies ){
  this->energies_ = std::move( energies );
  return *this;
}
