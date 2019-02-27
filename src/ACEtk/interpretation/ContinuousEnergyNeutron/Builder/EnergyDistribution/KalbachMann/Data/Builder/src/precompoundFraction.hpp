template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& precompoundFraction( Range&& R ){
  this->precompoundFraction_ = std::move( R );
  return *this;
}
