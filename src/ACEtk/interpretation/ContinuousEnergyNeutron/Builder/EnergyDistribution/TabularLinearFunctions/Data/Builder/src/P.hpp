template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& P( Range&& P ){
  this->P_ = std::move( P );
  return *this;
}
