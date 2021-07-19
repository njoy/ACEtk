template< typename T >
static decltype(auto)
fetch( T&& sequence, std::size_t index ) {

  // verify the index only in Debug build mode
  #ifndef NDEBUG
  verifyIndex( sequence, index );
  #endif

  // return the value (index is one-based so subtract 1)
  return sequence[index - 1];
}
