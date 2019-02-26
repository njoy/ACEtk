inline void interpolationParameter( const int& p ){
  if( not ( ( ( p >  0 ) and ( p <  7 ) ) or
            ( ( p > 10 ) and ( p < 16 ) ) or
            ( ( p > 20 ) and ( p < 26 ) ) )
    ){
    njoy::Log::error( "Invalid ENDF interpolation parameter: {}", p );
    throw details::verify::exceptions::InvalidENDFInterpolationParameter();
  }
}

template< typename Range, 
          utility::Require< true, utility::is_range, Range > = true >
inline void interpolationParameters( Range&& ps ){

  try{
    ranges::for_each( ps, interpolationParameter );
  } catch( details::verify::exceptions::InvalidENDFInterpolationParameter& e ){
    njoy::Log::info( "Invalid ENDF interpolation parameter found in array." );
    throw e;
  }
}
