template< typename Range,
          utility::Require< true, IsCosineBins, Range > = true >
auto cosineBins( Range&& r ){ return r; }

template< typename Range,
          utility::Require< false, IsCosineBins, Range > = true,
          utility::Require< true, utility::is_range, Range > = true >
auto cosineBins( Range&& r ){
  return CosineBins< std::decay_t< Range > >{ std::forward< Range >( r ) };
}

