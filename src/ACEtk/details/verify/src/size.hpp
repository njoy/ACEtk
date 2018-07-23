template< typename R1, typename R2,
          utility::Require< true, utility::is_range, R1 > = true,
          utility::Require< true, utility::is_range, R2 > = true
        >
inline void equalSize( R1&& a1, R2&& a2 ){
  if( a1.size() != a2.size() ){
    njoy::Log::error( "array sizes are not the same" );
    njoy::Log::info( "size1: {}, size2: {}", a1.size(), a2.size() );
    throw std::range_error( "array sizes are not the same" );
  }
}
