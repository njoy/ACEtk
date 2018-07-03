template< typename Range >
inline bool sorted( Range& array ){

  auto sortedEnd = ranges::is_sorted_until( array );
  if( sortedEnd != array.end() ){
    njoy::Log::error( "array is not sorted");
    njoy::Log::info( "first non-sorted element is: {} at index: {}", 
                     *sortedEnd, ( sortedEnd - array.begin() ) );
    return false;
  }
  return true;
}

template< typename Range >
inline bool sorted_positive( Range& array ){
  if( sorted( array ) ){
    if( *( array.begin() ) < 0.0 ){
      njoy::Log::error( "array is not all positive" );
      return false;
    }

    return true;
  }

  return false;
}

template< typename Range >
inline bool sorted_strictlyPositive( Range& array ){
  if( sorted( array ) ){
    if( *( array.begin() ) <= 0.0 ){
      njoy::Log::error( "array is not strictly positive" );
      return false;
    }

    return true;
  }

  return false;
}
