template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
inline auto isSorted( const Range& range ){

  return Sorted< Range >{ range };
}

template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
inline bool isSortedPositive( const Range& array ){
  return isPositive( Sorted< Range >( array ) );
}

template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
inline bool isSortedStrictlyPositive( const Range& array ){
  return isStrictlyPositive( Sorted< Range >( array ) );
}
