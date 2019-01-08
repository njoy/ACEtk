template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& boundaries( Range&& boundaries ){
  this->boundaries_ = std::move( boundaries );
  return *this;
}
