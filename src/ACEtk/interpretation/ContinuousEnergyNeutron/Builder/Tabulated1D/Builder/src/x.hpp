Derived& x( std::vector< double>&& x ){
  this->x_ = std::move( x );
  return static_cast< Derived& >( *this );
}
