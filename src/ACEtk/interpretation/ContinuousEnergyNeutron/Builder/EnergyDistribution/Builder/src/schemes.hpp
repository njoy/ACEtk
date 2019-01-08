template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& schemes( Range&& schemes ){
  this->schemes_ = std::move( schemes );
  return *this;
}
