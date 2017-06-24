auto& XSS( std::size_t index ){ return fetch(this->xss, index); }

CONST_OVERLOAD( XSS )

auto XSS( std::size_t index, std::size_t length ){
  #ifndef NDEBUG
  verifyIndex( this->xss, index );
  verifyIndex( this->xss, index + length - 1 );
  #endif
  const auto left = std::next( this->xss.begin(), index - 1 );
  const auto right = left + length;
  return ranges::make_iterator_range( left, right );
}

auto& XSS(){ return this->xss; }

auto XSS( std::size_t index, std::size_t length ) const {
  #ifndef NDEBUG
  verifyIndex( this->xss, index );
  verifyIndex( this->xss, index + length - 1 );
  #endif
  const auto left = std::next( this->xss.begin(), index - 1 );
  const auto right = left + length;
  return ranges::make_iterator_range( left, right );
}

const auto& XSS() const { return this->xss; }
