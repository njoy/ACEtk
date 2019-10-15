template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Derived& schemes( Range&& schemes ){
  details::verify::interpolationParameters( schemes );
  try {
    this->schemes_ = std::move( schemes );
  } catch( details::verify::exceptions::NotPositive& ){
    Log::info( "Tabulated schemes must be all positive." );
  }
  return static_cast< Derived& >( *this );
}
