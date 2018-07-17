template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
inline bool isSorted( const Range& array ){

  auto sortedEnd = ranges::is_sorted_until( array );
  if( sortedEnd != array.end() ){
    njoy::Log::error( "array is not sorted");
    auto index = sortedEnd - array.begin();
    njoy::Log::info( "first non-sorted element is: {} at index: {}", 
                     *sortedEnd, index );
    njoy::Log::info( "Value at index: {} is: {}", index-1, *(sortedEnd-1) );
    return false;
  }
  return true;
}

template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
inline bool isSortedPositive( const Range& array ){
  if( isSorted( array ) ){
    if( *( array.begin() ) < 0.0 ){
      njoy::Log::error( "array is not all positive" );
      return false;
    }

    return true;
  }

  return false;
}

template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
inline bool isSortedStrictlyPositive( const Range& array ){
  if( isSorted( array ) ){
    if( *( array.begin() ) <= 0.0 ){
      njoy::Log::error( "array is not strictly positive" );
      return false;
    }

    return true;
  }

  return false;
}
