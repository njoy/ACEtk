template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& cosineGrid( Range&& cosines ){
  this->cosineGrid_ = std::move( cosines );
  return *this;
}
