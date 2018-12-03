auto& XSS( std::size_t index ){ return fetch(this->xss, index); }

CONST_OVERLOAD( XSS )

ranges::iterator_range< std::vector< double >::iterator >
XSS( std::size_t index, std::size_t length ){
#ifndef NDEBUG
  verifyIndex( this->xss, index );
  verifyIndex( this->xss, index + length - 1 );
#endif
  const auto left = std::next( this->xss.begin(), index - 1 );
  const auto right = left + length;
  return ranges::make_iterator_range( left, right );
}

auto& XSS(){ return this->xss; }

ranges::iterator_range< std::vector< double >::const_iterator >
XSS( std::size_t index, std::size_t length ) const {
#ifndef NDEBUG
  verifyIndex( this->xss, index );
  verifyIndex( this->xss, index + length - 1 );
#endif
  const auto left = std::next( this->xss.begin(), index - 1 );
  const auto right = left + length;
  return ranges::make_iterator_range( left, right );
}

const auto& XSS() const { return this->xss; }
