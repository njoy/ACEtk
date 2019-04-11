template< typename R1, typename... R2,
          utility::Require< true, utility::is_range, R1 > = true,
          std::enable_if_t< 
            all( utility::is_range< R2 >::value... ), bool > = true >
void equalSize( const R1& a1, const R2&... a2 ){
  auto d1 = ranges::distance( a1 );

  if( not all( ( d1 == ranges::distance( a2 ) )... ) ){
    njoy::Log::error( "ranges are not the same size" );
    njoy::Log::info( "a1 size: {}", d1 );
    njoy::Log::info( "a2 size: {}", ranges::distance( a2 )... );

    throw std::range_error( "array sizes are not the same" );
  }
}
