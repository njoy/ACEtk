template< typename Range,
          utility::Require< true, IsStrictlyPositive, Range > = true >
auto isStrictlyPositive( Range&& r ){ return r; }

template< typename Range,
          utility::Require< false, IsStrictlyPositive, Range > = true,
          utility::Require< true, utility::is_range, Range > = true >
auto isStrictlyPositive( Range&& r ){
  return StrictlyPositive< std::decay_t< Range > >
  { std::forward< Range >( r ) };
}
