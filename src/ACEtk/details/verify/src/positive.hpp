template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
inline bool positive( const Range& array ){
  auto firstNegative = ranges::count_if( array, 
    [](auto& e ){ return e < 0.0; } );

  if( firstNegative > 0 ){
    njoy::Log::error( "All elements of the array must be positive" );
    njoy::Log::info( "Found {} negative array elements", firstNegative );
    return false;
  }

  return true;
}

template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
inline bool strictlyPositive( const Range& array ){
  auto firstNegative = ranges::count_if( array, 
    [](auto& e ){ return e <= 0.0; } );

  if( firstNegative > 0 ){
    njoy::Log::error( "All elements of the array must be positive" );
    njoy::Log::info( "Found {} negative array elements", firstNegative );
    return false;
  }

  return true;
}
