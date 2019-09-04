template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Derived& schemes( Range&& schemes ){
  details::verify::interpolationParameters( schemes );
  this->schemes_ = std::move( schemes );
  return static_cast< Derived& >( *this );
}
