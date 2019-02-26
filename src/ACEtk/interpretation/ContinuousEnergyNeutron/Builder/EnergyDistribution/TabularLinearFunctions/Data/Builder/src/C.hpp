template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& C( Range&& C ){
  this->C_ = std::move( C );
  return *this;
}
