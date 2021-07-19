/**
 *  @brief Return the XSS array
 */
auto& XSS() {

  return this->xss_;
}

/**
 *  @brief Return the XSS array
 */
const auto& XSS() const {

  return this->xss_;
}

/**
 *  @brief Return an XSS value
 *
 *  The index value is one-based.
 *
 *  Range checking is only performed when NDEBUG is not defined. When the index
 *  is out of range, an std::out_of_range exception is thrown.
 */
auto& XSS( std::size_t index ) {

  return fetch( this->xss_, index );
}

/**
 *  @brief Return an XSS value
 *
 *  The index value is one-based.
 *
 *  Range checking is only performed when NDEBUG is not defined. When the index
 *  is out of range, an std::out_of_range exception is thrown.
 */
auto XSS( std::size_t index ) const {

  return fetch( this->xss_, index );
}

/**
 *  @brief Return a subrange of a given length from the XSS array
 *
 *  The index value is one-based.
 *
 *  Range checking is only performed when NDEBUG is not defined. When the index
 *  is out of range or if the array goes over its length, an std::out_of_range
 *  exception is thrown.
 */
auto XSS( std::size_t index, std::size_t length ){

  #ifndef NDEBUG
  verifyIndex( this->xss_, index );
  verifyIndex( this->xss_, index + length - 1 );
  #endif
  const auto left = std::next( this->xss_.begin(), index - 1 );
  const auto right = left + length;
  return ranges::make_iterator_range( left, right );
}

/**
 *  @brief Return a subrange of a given length from the XSS array
 *
 *  The index value is one-based.
 *
 *  Range checking is only performed when NDEBUG is not defined. When the index
 *  is out of range or if the array goes over its length, an std::out_of_range
 *  exception is thrown.
 */
auto XSS( std::size_t index, std::size_t length ) const {
  
  #ifndef NDEBUG
  verifyIndex( this->xss_, index );
  verifyIndex( this->xss_, index + length - 1 );
  #endif
  const auto left = std::next( this->xss_.begin(), index - 1 );
  const auto right = left + length;
  return ranges::make_iterator_range( left, right );
}
