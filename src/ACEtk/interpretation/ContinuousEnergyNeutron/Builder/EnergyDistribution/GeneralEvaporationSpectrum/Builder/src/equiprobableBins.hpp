template< typename Range,
utility::Require< true, utility::is_range, Range > = true >
Builder& equiprobableBins( Range&& bins ){
  this->equiprobableBins_ = std::move( bins );
  return *this;
}
