template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Derived& schemes( Range&& schemes ){
  this->schemes_ = std::move( details::verify::positive( schemes ) );
  return static_cast< Derived& >( *this );
}
