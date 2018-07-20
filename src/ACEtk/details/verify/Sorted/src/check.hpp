template< typename Arg,
          utility::Require< true, utility::is_range, Range > = true >
decltype( auto ) check( Arg&& arg ){
  auto sortedEnd = ranges::is_sorted_until( arg );
  if( sortedEnd != arg.end() ){
    auto index = sortedEnd - arg.begin();

    njoy::Log::error( "range is not sorted");
    njoy::Log::info( "first non-sorted element is: {} at index: {}", 
                     *sortedEnd, index );
    njoy::Log::info( "Value at index: {} is: {}", index-1, *(sortedEnd-1) );
    throw UnsortedException( "range is not sorted" );
  }
  return std::forward< Arg >( arg );
}
