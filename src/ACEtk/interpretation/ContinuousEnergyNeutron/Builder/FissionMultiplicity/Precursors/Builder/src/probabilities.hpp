template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Builder& probabilities( Range&& pdf ){
  this->y( std::move( details::verify::positive( pdf ) ) );
  return *this;
}
