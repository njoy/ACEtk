template< typename T >
static decltype(auto) fetch( T&& value ){ return value; }

template< typename T, int i >
static decltype(auto)
fetch( T&& value, Index<i> ){ return std::get<i>(value); }

template< typename T, typename... Args >
static decltype(auto)
fetch( T&& sequence, std::size_t index, Args&&... args ){
  #ifndef NDEBUG
  verifyIndex( sequence, index, std::forward<Args>(args)... );
  #endif
  return fetch( sequence[index - 1], std::forward<Args>(args)... );
}
