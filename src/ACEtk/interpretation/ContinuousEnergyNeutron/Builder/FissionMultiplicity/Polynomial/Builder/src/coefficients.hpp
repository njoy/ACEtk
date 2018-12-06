template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& coefficients( Range&& coeffs ){
  this->coefficients_ = std::move( coeffs );
  return *this;
}
