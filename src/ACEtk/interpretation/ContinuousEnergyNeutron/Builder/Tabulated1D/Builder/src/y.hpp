Derived& y( std::vector< double>&& y ){
  this->y_ = std::move( y );
  return static_cast< Derived& >( *this );
}
