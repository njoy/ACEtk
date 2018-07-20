template< typename... Args, 
          utility::Require< true, std::is_constructible, Range, Args... > = true
        >
Sorted( Args&&... args ):
  Range( std::forward< Args >( args )... )
{
  auto sortedEnd = ranges::is_sorted_until( *this );
  if( sortedEnd != this->end() ){
    auto index = sortedEnd - this->begin();

    njoy::Log::error( "range is not sorted");
    njoy::Log::info( "first non-sorted element is: {} at index: {}", 
                     *sortedEnd, index );
    njoy::Log::info( "Value at index: {} is: {}", index-1, *(sortedEnd-1) );
    throw UnsortedException( "range is not sorted" );
  }
}
