inline void neutronYield( const int& y ){
  auto absy = abs( y );
  if( not (
      ( ( absy >= 0 ) and ( absy < 5  ) ) or
      ( absy == 19 ) or
      ( absy > 100 )
      ) ){
    Log::error( "Invalid neutron yield value: {}", y );
    Log::info( 
      "valid values are: 0, +-1, +-2, +-3, +-4, +-10, < 100, and > 100" );
    throw details::verify::exceptions::InvalidNeutronYield();
  }
}
