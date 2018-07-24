template< typename R1, typename R2 >
inline void equalSize( R1&& a1, R2&& a2 ){
  if( ranges::distance( a1 ) != ranges::distance( a2 ) ){
    njoy::Log::error( "array sizes are not the same" );
    njoy::Log::info( "size1: {}, size2: {}", 
        ranges::distance( a1 ), ranges::distance( a2 ) );

    throw std::range_error( "array sizes are not the same" );
  }
}
