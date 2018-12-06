template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Derived& y( Range&& y ){
  this->y_ = std::move( y );
  return static_cast< Derived& >( *this );
}
