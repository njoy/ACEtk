template< typename Range,
          utility::Require< true, IsNormal, Range > = true >
auto normal( Range&& r ){ return r; }

template< typename Range,
          utility::Require< false, IsNormal, Range > = true,
          utility::Require< true, utility::is_range, Range > = true >
auto normal( Range&& r ){
  return Normal< std::decay_t< Range > >{ std::forward< Range >( r ) };
}
