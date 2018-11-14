template< typename Arg,
          utility::Require< true, IsSorted, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  return std::forward< Arg >( arg );
}

template< typename Arg,
          utility::Require< false, IsSorted, Arg > = true,
          utility::Require< true, utility::is_range, Arg > = true >
static decltype( auto ) check( Arg&& arg ){
  const auto sortedEnd = ranges::is_sorted_until( arg );
  if( sortedEnd != arg.end() ){
    const auto index = std::distance( arg.begin(), sortedEnd );

    njoy::Log::error( "range is not sorted");
    njoy::Log::info( "first non-sorted element is: {} at index: {}",
                     *sortedEnd, index );
    njoy::Log::info( "Value at index: {} is: {}", index-1, *(sortedEnd-1) );
    throw exceptions::Unsorted( "range is not sorted" );
  }
  return std::forward< Arg >( arg );
}
