template< typename Range,
          utility::Require< true, IsPDF, Range > = true >
auto pdf( Range&& r ){ return r; }

template< typename Range,
          utility::Require< false, IsPDF, Range > = true,
          utility::Require< true, utility::is_range, Range > = true >
auto pdf( Range&& r ){
  return PDF< std::decay_t< Range > >{ std::forward< Range >( r ) };
}
