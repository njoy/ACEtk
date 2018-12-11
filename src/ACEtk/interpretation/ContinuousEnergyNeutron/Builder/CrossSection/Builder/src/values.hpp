template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
Derived& values( Range&& xs ){
  try{
    this->values_ = std::move( details::verify::positive( xs ) );
    return static_cast< Derived& >( *this );
  } catch( details::verify::exceptions::NotPositive& e ){
    Log::info( "Cross section values must be all positive" );
    throw;
  }
}
