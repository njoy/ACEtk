template< typename Range,
          utility::Require< true, IsCDF, Range > = true >
auto cdf( Range&& r ){ return r; }

template< typename Range,
          utility::Require< false, IsCDF, Range > = true,
          utility::Require< true, utility::is_range, Range > = true >
auto cdf( Range&& r ){
  return CDF< std::decay_t< Range > >{ std::forward< Range >( r ) };
}
