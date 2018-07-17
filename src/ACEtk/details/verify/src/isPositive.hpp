template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
inline bool isPositive( const Range& array ){
  auto firstNegative = ranges::find_if( array, 
    [](auto& e ){ return e < 0; } );

  if( firstNegative != std::end( array ) ){
    njoy::Log::error( "All elements of the array must be positive" );
    njoy::Log::info( "First negative element ({}) found at index: {}",
                     *firstNegative, ( firstNegative - array.begin() ) );
    return false;
  }

  return true;
}

template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
inline bool isStrictlyPositive( const Range& array ){
  auto firstNegative = ranges::find_if( array, 
    [](auto& e ){ return e <= 0; } );

  if( firstNegative != std::end( array ) ){
    njoy::Log::error( "All elements of the array must be positive" );
    njoy::Log::info( 
        "First non strictly positive element ({}) found at index: {}",
        *firstNegative, ( firstNegative - array.begin() ) );
    return false;
  }

  return true;
}
