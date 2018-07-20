template< typename Range,
          utility::Require< false, IsPositive, Range > = true,
          utility::Require< true, utility::is_range, Range > = true 
        >
auto positive( Range&& r ){
  return Sorted< std::decay_t< Range > >{ std::forward< Range >( r ) };
}

template< typename Range,
          utility::Require< true, IsPositive, Range > = true 
        >
auto positive( Range&& r ){
  return r;
}


