template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& pdf( Range&& pdf ){
  this->pdf_ = std::move( pdf );
  return *this;
}
