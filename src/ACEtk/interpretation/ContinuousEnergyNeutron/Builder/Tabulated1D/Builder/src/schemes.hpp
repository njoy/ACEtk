Derived& schemes( std::vector< double>&& schemes ){
  this->schemes_ = std::move( schemes );
  return static_cast< Derived& >( *this );
}
