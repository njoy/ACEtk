template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& cosines( Range&& cosines ){
  this->cosines_ = std::move( cosines );
  return *this;
}
