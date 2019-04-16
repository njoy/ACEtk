template< typename T, 
          typename... Args,
          utility::Require< true, hasACEify, T, Args... > = true
        >
void ACEify( Table::Data& d, T& t, Args&... args );

template< typename... Ts, typename... Args >
void ACEify( Table::Data& data, std::variant< Ts... >& v, Args&... args ){
  std::visit( [ & ]( auto&& t ){ ACEify( data, t, args... ); }, v );
}

template< typename T, 
          typename... Args,
          utility::Require< true, hasACEify, T, Args... > = true
        >
void ACEify( Table::Data& d, T& t, Args&... args ){
  t.ACEify( d, args... );
}
