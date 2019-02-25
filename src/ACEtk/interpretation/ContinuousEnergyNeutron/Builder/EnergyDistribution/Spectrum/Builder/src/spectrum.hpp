Derived& spectrum( S&& spectrum ){
  this->spectrum_ = std::move( spectrum );
  return static_cast< Derived& >( *this );
}
