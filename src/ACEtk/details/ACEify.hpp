/* Declarations */
inline void ACEify( Table::Data& d, double t ){
  d.XSS().push_back( t );
}

template< typename T, 
          typename... Args,
          utility::Require< true, hasACEify, T, Args... > = true
        >
void ACEify( Table::Data& d, T& t, Args&&... args );

template< typename T, 
          typename... Args,
          utility::Require< false, hasACEify, T, Args... > = true,
          utility::Require< true, utility::is_range, T > = true
        >
void ACEify( Table::Data& d, T& t, Args&&... args );

template< typename... Ts, typename... Args >
void ACEify( Table::Data& data, std::variant< Ts... >& v, Args&&... args );

/* Definitions */

template< typename T, 
          typename... Args,
          utility::Require< true, hasACEify, T, Args... >
        >
void ACEify( Table::Data& d, T& t, Args&&... args ){
  t.ACEify( d, args... );
}

template< typename T, 
          typename... Args,
          utility::Require< false, hasACEify, T, Args... >,
          utility::Require< true, utility::is_range, T >
        >
void ACEify( Table::Data& d, T& t, Args&&... args ){
  for( auto& ele : t ){
    ACEify( d, ele, args... );
  }
}

template< typename... Ts, typename... Args >
void ACEify( Table::Data& data, std::variant< Ts... >& v, Args&&... args ){
  std::visit( [ & ]( auto&& t ){ details::ACEify( data, t, args... ); }, v );
}
