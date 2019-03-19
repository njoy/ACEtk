inline constexpr bool all(){ return true; }

template< typename... Ts >
constexpr bool all( bool b, Ts... bs ){
  return b and all( bs... );
}
