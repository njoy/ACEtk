template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& heating( Range&& heat ){
  this->heating_ = std::move( heat );
  return *this;
}
