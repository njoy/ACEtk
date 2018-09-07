template< typename Range,
          utility::Require< true, IsSorted, Range > = true >
auto sorted( Range&& r ){
  return r;
}

template< typename Range,
          utility::Require< false, IsSorted, Range > = true,
          utility::Require< true, utility::is_range, Range > = true >
auto sorted( Range&& r ){
  return Sorted< std::decay_t< Range > >{ std::forward< Range >( r ) };
}
