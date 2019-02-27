template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& angularDistributionSlope( Range&& A ){
  this->angularDistributionSlope_ = std::move( A );
  return *this;
}
