template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
inline bool isPositive( const Range& range ){
  auto firstNegative = ranges::find_if( range, [](auto& e ){ return e < 0; } );

  if( firstNegative != std::end( range ) ){
    njoy::Log::error( "All elements of the range must be positive" );
    njoy::Log::info( "First negative element ({}) found at index: {}",
                     *firstNegative, ( firstNegative - range.begin() ) );
    return false;
  }

  return true;
}

template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
inline bool isStrictlyPositive( const Range& range ){
  auto firstNonPositive = ranges::find_if( 
      range, [](auto& e ){ return e <= 0; } );

  if( firstNonPositive != std::end( range ) ){
    njoy::Log::error( "All elements of the range must be positive" );
    njoy::Log::info( 
        "First non strictly positive element ({}) found at index: {}",
        *firstNonPositive, ( firstNonPositive - range.begin() ) );
    return false;
  }

  return true;
}
