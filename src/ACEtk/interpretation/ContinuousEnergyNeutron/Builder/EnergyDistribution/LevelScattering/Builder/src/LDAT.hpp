template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& LDAT( Range&& ldat ){
  this->LDAT_ = ldat;
  return *this;
}
