template< typename Range >
inline bool positive( Range& array ){
  auto firstNegative = ranges::count_if( array, 
    [](auto& e ){ return e < 0.0; } );

  if( firstNegative > 0 ){
    njoy::Log::error( "All elements of the array must be positive" );
    njoy::Log::info( "Found {} negative array elements", firstNegative );
    return false;
  }

  return true;
}

template< typename Range >
inline bool strictlyPositive( Range& array ){
  auto firstNegative = ranges::count_if( array, 
    [](auto& e ){ return e <= 0.0; } );

  if( firstNegative > 0 ){
    njoy::Log::error( "All elements of the array must be positive" );
    njoy::Log::info( "Found {} negative array elements", firstNegative );
    return false;
  }

  return true;
}
