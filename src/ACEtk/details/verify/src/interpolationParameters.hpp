inline bool interpolationParameter( int p ){
  if( not ( ( ( p >  0 ) and ( p <  7 ) ) or
            ( ( p > 10 ) and ( p < 16 ) ) or
            ( ( p > 20 ) and ( p < 26 ) ) )
    ){
    njoy::Log::error( "Invalid ENDF interpolation parameter: {}", p );
    return false;
  }
  return true;
}

template< typename V, utility::Require< true, utility::is_range, V > = true >
inline bool interpolationParameters( V&& ps ){

  auto all = ranges::all_of( ps, interpolationParameter );
  if( not all ){
    njoy::Log::info( "Invalid ENDF interpolation parameter found in array." );
    return false;
  }
  return true;
}
