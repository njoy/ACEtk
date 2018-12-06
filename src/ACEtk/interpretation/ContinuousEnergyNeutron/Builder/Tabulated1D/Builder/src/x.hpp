template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Derived& x( Range&& x ){
  this->x_ = std::move( x );
  return static_cast< Derived& >( *this );
}
