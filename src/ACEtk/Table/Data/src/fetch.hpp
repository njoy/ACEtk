template< typename T >
static decltype(auto)
fetch( T&& sequence, std::size_t index ){
  #ifndef NDEBUG
  verifyIndex( sequence, index );
  #endif
  return sequence[index - 1];
}

