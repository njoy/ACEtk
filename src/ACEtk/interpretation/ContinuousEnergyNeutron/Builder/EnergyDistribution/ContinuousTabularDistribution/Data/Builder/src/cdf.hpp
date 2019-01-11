template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& cdf( Range&& cdf ){
  this->cdf_ = std::move( cdf );
  return *this;
}

