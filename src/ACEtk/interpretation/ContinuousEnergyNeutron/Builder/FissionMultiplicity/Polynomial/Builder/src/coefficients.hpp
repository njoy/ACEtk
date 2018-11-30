Builder& coefficients( std::vector< double>&& coeffs ){
  this->coefficients_ = std::move( coeffs );
  return *this;
}
