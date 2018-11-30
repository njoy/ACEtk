Derived& boundaries( std::vector< double>&& boundaries ){
  this->boundaries_ = std::move( boundaries );
  return static_cast< Derived& >( *this );
}
