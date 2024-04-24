/**
 *  @brief Return a subrange of a given length from the XSS array
 *
 *  Range checking is only performed when NDEBUG is not defined. When the index
 *  is out of range or if the array goes over its length, an std::out_of_range
 *  exception is thrown.
 *
 *  @param[in] index     the index (one-based)
 *  @param[in] length    the length of the subrange
 */
auto XSS( std::size_t index, std::size_t length ){

  #ifndef NDEBUG
  verifyIndex( this->xss_, index );
  verifyIndex( this->xss_, index + length - 1 );
  #endif
  const auto left = std::next( this->xss_.begin(), index - 1 );
  const auto right = left + length;
  return njoy::tools::std20::ranges::subrange( left, right );
}

/**
 *  @brief Return a subrange of a given length from the XSS array
 *
 *  Range checking is only performed when NDEBUG is not defined. When the index
 *  is out of range or if the array goes over its length, an std::out_of_range
 *  exception is thrown.
 *
 *  @param[in] index     the index (one-based)
 *  @param[in] length    the length of the subrange
 */
auto XSS( std::size_t index, std::size_t length ) const {

  #ifndef NDEBUG
  verifyIndex( this->xss_, index );
  verifyIndex( this->xss_, index + length - 1 );
  #endif
  const auto left = std::next( this->xss_.begin(), index - 1 );
  const auto right = left + length;
  return njoy::tools::std20::ranges::subrange( left, right );
}
